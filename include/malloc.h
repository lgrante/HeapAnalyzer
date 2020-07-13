#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define META_DATA size_t
#define META_SIZE sizeof(META_DATA)

#define META(ptr) (*((META_DATA *) ptr))

#define IS_BLOCK_ALLOC(ptr) ((META(ptr)\
    << ((META_SIZE * 8) - 1)) >> ((META_SIZE * 8) - 1))
#define GET_BLOCK_SIZE(ptr) (META(ptr) >> 1)

#define SET_BLOCK_ALLOC(ptr, alloc) (META(ptr) = ((META(ptr)\
    >> 1) << 1) | alloc)
#define SET_BLOCK_SIZE(ptr, size) (META(ptr) = IS_BLOCK_ALLOC(ptr)\
    | (size << 1))

#define ALLOC_BLOCK(ptr, size, alloc) {\
    SET_BLOCK_SIZE(ptr, size);\
    SET_BLOCK_ALLOC(ptr, alloc);\
}

#define MALLOC_ERR(message) {\
    write(2, __func__, strlen(__func__));\
    write(2, "(): ", 5);\
    write(2, message, strlen(message));\
    putchar('\n');\
    abort();\
}

/**
 * @note: Extern variables.
 * 
 */
extern void *page_start;
extern void *blocks_end;

/**
 * @note: Standard malloc functions.
 */

void *malloc(size_t bytes);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

#endif
