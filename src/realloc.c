#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
    void *new = NULL;
    void *prev_block = NULL;
    size_t prev_block_sz = 0;

    if (ptr == NULL)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    prev_block = ptr - META_SIZE;
    prev_block_sz = GET_BLOCK_SIZE(prev_block);
    if (size < prev_block_sz)
        return ptr;
    new = malloc(size);
    if (new == NULL)
        return (NULL);
    for (int i = 0; i < prev_block_sz; i++)
        ((char *) new)[i] = ((char *) ptr)[i];
    free(ptr);
    return new;
}