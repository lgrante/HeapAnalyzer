#include "malloc.h"
#include "debug.h"

static unsigned int my_pow(int number, int exponent)
{
    unsigned int res = 1;

    for (int i = 0; i < exponent; i++)
        res *= number;
    return res;
}

static int count_digit(int number)
{
    uint8_t ct = 0;

    if (number == 0)
        return 1;
    while (number != 0) {
        number /= 10;
        ct++;
    }
    return ct;
}

void printchr(char const c)
{
    write(1, &c, 1);
}

void printstr(char const *str)
{
    write(1, str, strlen(str));
}

void printnum(uint64_t num)
{
    int p = 1;
    int exponent = 0;
    char digit = 0;

    while(p <= num) {
        p *= 10;
        exponent++;
    }
    p = my_pow(10, exponent - 1);
    for (int i = 0; p > 0; i++) {
        digit = (num / p) + '0';
        write(1, &digit, 1);
        num = num % p;
        p /= 10;
    }
}

void printhexa(int num)
{
    char base[16] = "0123456789abcdef";
    char hexa[20];
    int digits = 0;
    int remainder;

    if (num < 0)
        num = (~num) + 1;
    while (num != 0) {
        remainder = num % 16;
        hexa[digits++] = base[remainder];
        num /= 16;
    }
    for (int i = digits; i >= 0; i--)
        printchr(hexa[i]);
}

void space(uint8_t space)
{
    for (int i = 0; i < space; i++)
        printchr(' ');
}

void printblock(void *block)
{
    size_t block_sz = GET_BLOCK_SIZE(block);
    void *block_user_data = block + META_SIZE;

    printstr("\e[1m [\e[0m");
    printnum(block_sz);
    space(8 - count_digit(block_sz));
    printstr(" bytes ");
    if (IS_BLOCK_ALLOC(block))
        printstr("\e[1m|\e[0m \e[38;2;255;35;0mAllocated\033[0m");
    else
        printstr("\e[1m|\e[0m \e[38;2;0;255;35mFree     \033[0m");
    printstr(" \e[1m| Data:\e[0m ");
    for (int i = 0; i < 100; i++) {
        if (((char *) block_user_data)[i] >= ' ' && ((char *) block_user_data)[i] <= '~')
            printchr(((char *) block_user_data)[i]);
        else
            printchr('.');
    }
    printstr("\e[1m]\e[0m\n");
}

void printpage(void *page_start, int block_nb)
{
    int i = 0;

    while (page_start < blocks_end && (i < block_nb || block_nb == -1)) {
        printstr("\e[38;2;229;94;16m");
        printnum(i);
        printstr("\033[0m");
        space(4 - count_digit(i));
        printblock(page_start);
        page_start += (GET_BLOCK_SIZE(page_start) + META_SIZE);
        i++;
    }
}