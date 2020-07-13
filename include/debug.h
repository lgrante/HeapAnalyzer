#ifndef DEBUG_H
#define DEBUG_H

#include <string.h>
#include <stdint.h>

#define DEBUG(var) {\
    printstr(#var);\
    printstr(": ");\
    printnum(var);\
    printstr("\n");\
} 

#define DEBUG_BITS(var, size) {\
    printstr(#var);\
    printstr(": ");\
    for (int i = size; i >= 0; i--) {\
        printnum((var >> i) & 1);\
    }\
    printstr("\n");\
}

#define DEBUG_ALLOC(size) {\
    space(25);\
    printstr("\e[1m\e[38;2;21;124;214m*HEAP SUMMARY*\033[0m\e[0m\n\n");\
    printstr("\e[1m\e[38;2;229;94;16m>>   [");\
    printstr(__func__);\
    printstr(" of size: ");\
    printnum(size);\
    printstr("]\033[0m\e[0m\n");\
    printpage(page_start, BLOCK_NB);\
    printstr("...\n\n");\
}

void printchr(char const c);
void printstr(char const *str);
void printnum(uint64_t num);
void space(uint8_t space);

void printblock(void *addr);
void printpage(void *page_start, int block_nb);

#endif
