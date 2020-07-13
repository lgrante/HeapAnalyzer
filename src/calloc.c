#include "malloc.h"

void *calloc(size_t nmemb, size_t size)
{
    void *ptr = malloc(nmemb * size);
    void *block = NULL;
    size_t block_sz = 0;

    if (ptr == NULL)
        return NULL;
    block = ptr - META_SIZE;
    block_sz = GET_BLOCK_SIZE(block);
    for (unsigned int i = 0; i < block_sz; i++)
        ((char *) ptr)[i] = 0;
    return ptr;
}