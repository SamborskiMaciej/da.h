#include <stdio.h>

#define DA_IMPLEMENTATION
#include "da.h"

void printDa(void * item)
{
    printf("%hu\n", *((unsigned short *) item));
}

int main(void)
{
    unsigned short * da = daCreate(unsigned short, 1);

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

    x = 1667;
    daPush(da, x);
    daPop(da, x);
    printf("popd: %hu\n", x);

    daForeach(da, printDa);

    printf("%zu %zu %zu\n", daSize(da), daCap(da), daType(da));

    char * da2 = daCreate(char, 1);

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
    y = '!';
    daPush(da2, y);

    heapstr message = daToCStr(da2);

    printf("%s\n", message);
    free(message);

    daFree(da);
    daFree(da2);
}
