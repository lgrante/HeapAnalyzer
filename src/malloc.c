#include "malloc.h"

void *page_start = NULL;
void *blocks_end = NULL;

static void *push_break_alloc(size_t size)
{
    void *block = NULL;
    META_DATA metadata = 0;
    size_t multiple_off = 2;
    size_t page_sz = getpagesize();
    size_t brk_off = 0;
    
    if (blocks_end + META_SIZE + size >= sbrk(0)) {
        while (size >= multiple_off * page_sz)
            multiple_off += 2;
        brk_off = multiple_off * page_sz;
        sbrk(brk_off);
    }
    block = blocks_end;
    ALLOC_BLOCK(&metadata, size, 1);
    META(block) = metadata;
    blocks_end = block + META_SIZE + size;
    return block;
}

static void split_block_alloc(void *block, size_t size)
{
    META_DATA metadata = 0;
    META_DATA next_metadata = 0;
    void *next_block = NULL;
    size_t block_sz = GET_BLOCK_SIZE(block);

    if (block_sz == size || block_sz - META_SIZE == size) {
        ALLOC_BLOCK(&metadata, block_sz, 1);
        META(block) = metadata;
    } else {
        next_block = block + META_SIZE + size;
        ALLOC_BLOCK(&metadata, size, 1);
        ALLOC_BLOCK(&next_metadata, (block_sz - size - META_SIZE), 0);
        META(block) = metadata;
        META(next_block) = next_metadata;
    }
}

static void *find_block(size_t size)
{
    void *block = page_start;
    void *sm_block = NULL;
    size_t sm_block_sz = 0;
    size_t crt_block_sz = 0;

    while (block < blocks_end) {
        crt_block_sz = GET_BLOCK_SIZE(block);
        if (!IS_BLOCK_ALLOC(block) && crt_block_sz >= size) {
            sm_block_sz = sm_block_sz == 0 ? crt_block_sz : sm_block_sz;
            if (crt_block_sz <= sm_block_sz) {
                sm_block_sz = crt_block_sz;
                sm_block = block;
            }
        }
        block += (crt_block_sz + META_SIZE);
    }
    return sm_block;
}

void *malloc(size_t size)
{
    void *sm_block = NULL;

    if (size == 0)
        return NULL;
    size = ((size + (sizeof(void *) - 1)) & (~(sizeof(void *) - 1)));
    if (page_start == NULL) {
        page_start = sbrk(0);
        blocks_end = page_start;
    }
    sm_block = find_block(size);
    if (sm_block == NULL)
        sm_block = push_break_alloc(size);
    else
        split_block_alloc(sm_block, size);
#ifdef DEBUG_MODE
#include "debug.h"
    DEBUG_ALLOC(size);
#endif
    return sm_block + META_SIZE;
}
