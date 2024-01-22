#include <stdio.h>

#define DA_IMPLEMENTATION
#include "da.h"

void printDaU16(void * item)
{
    printf("%hu\n", *((unsigned short *) item));
}

void printDaS32(void * item)
{
    printf("%hu\n", *((int *) item));
}

int main(void)
{
    printf("----------\n");
    printf("DA1\n");
    printf("----------\n");

    dynarr(unsigned short) * da = daCreate(unsigned short, 1);

    unsigned short x = 69;
    daPush(da, x);
    x = 42069;
    daPush(da, x);
    x = 1337;
    daPush(da, x);
    x = 34;
    daPush(da, x);
    x = 35;
    daPush(da, x);
    x = 1667;

    daPush(da, x);
    daPop(da, x);
    printf("x: %hu\n", x);

    daForeach(da, printDaU16);

    printf("%zu %zu %zu\n", daSize(da), daCap(da), daType(da));

    printf("----------\n");
    printf("DA2\n");
    printf("----------\n");

    dynarr(char) da2 = daCreate(char, 1);

    char y = 'H';
    daPush(da2, y);
    y = 'i';
    daPush(da2, y);
    y = ' ';
    daPush(da2, y);
    y = 'm';
    daPush(da2, y);
    y = 'o';
    daPush(da2, y);
    y = 'm';
    daPush(da2, y);
    y = '?';
    daPush(da2, y);

    *(char *)daGetRef(da2, 6) = '!';

    heapstr message = daToCStr(da2);

    printf("%s\n", message);
    free(message);

    daFree(da);
    daFree(da2);
}
