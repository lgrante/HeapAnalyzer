#include "malloc.h"

void free(void *ptr)
{
    void *block = NULL;
    META_DATA metadata = 0;

    if (ptr == NULL)
        return;
    block = ptr - META_SIZE;
    metadata = META(block);
    SET_BLOCK_ALLOC(&metadata, 0);
    META(block) = metadata;
#ifdef DEBUG_MODE
#include "debug.h"
    DEBUG_ALLOC(GET_BLOCK_SIZE(block));
#endif
}