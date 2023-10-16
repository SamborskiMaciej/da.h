#ifndef DA_H_
#define DA_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum daFields {
    SIZE          = 0,
    CAPACITY      = 1,
    TYPE          = 2,
    DATA          = 3,
};
                                       
void * _daCreate(size_t initCapacity, size_t type, size_t size);
void * _daPush(void * da, void * item);
void _daPop(void * da, void * element);
void daFree(void * da);

size_t daSize(void * da);
size_t daCap(void * da);
size_t daType(void * da);

size_t * daField(void * da, enum daFields field);
typedef void(* func)(void * item);
void daForeach(void * da, func f);

typedef char * heapstr;
heapstr daToCStr(void * da);
void daBzero(void * da);

#define daCreate(type, cap) _daCreate(cap, sizeof(type), 0)
#define daPush(da, item) da = _daPush(da, &item)
#define daPop(da, item) _daPop(da, &item)

#endif // DA_H_
           
#ifdef DA_IMPLEMENTATION 

void * _daCreate(size_t cap, size_t type, size_t size)
{
    size_t * da = (size_t *) malloc(type * cap + DATA * sizeof(size_t));
    da[SIZE] = size;
    da[CAPACITY] = cap;
    da[TYPE] = type;

    return (void *) (da + DATA);
}                        

void daFree(void * da)
{
    free((size_t *) da - DATA);
}

void * daResize(void * da)
{
    void * temp = _daCreate(daCap(da) * 2, daType(da), daSize(da));
    memcpy(temp, da, daSize(da) * daType(da));
    daFree(da);
    return temp;
}

void * _daPush(void * da, void * item)
{
    if (daSize(da) >= daCap(da)) da = daResize(da);
    memcpy((char *)da + daSize(da) * daType(da), item, daType(da));
    *daField(da, SIZE) += 1;
    return da;
}

void _daPop(void * da, void * elem)
{   
    *daField(da, SIZE) -= 1;
    memcpy(elem, (char *)da + daSize(da) * daType(da), daType(da));
}

size_t * daField(void * da, enum daFields field)
{
    if (field < SIZE || field > TYPE)
    {
        fprintf(stderr, "*------------------------------*\n");
        fprintf(stderr, "ERROR: Wrong field: %d\n", field);
        fprintf(stderr, "AVAILABLE: SIZE, CAPACITY, TYPE\n");
        fprintf(stderr, "*------------------------------*\n");
        exit(1);
    }

    return ((size_t *) da - DATA + field);
}

size_t daSize(void * da)
{
    return ((size_t *) da - DATA)[SIZE];
}

size_t daCap(void * da)
{
    return ((size_t *) da - DATA)[CAPACITY];
}

size_t daType(void * da)
{
    return ((size_t *) da - DATA)[TYPE];
}

void daForeach(void * da, func f)
{
    for (size_t i = 0; i < daSize(da); ++i)
        f((char *) da + i * daType(da));
}

heapstr daToCStr(void * da)
{
    char * buffer = (char *) calloc(1, daSize(da) + 1);
    memcpy(buffer, da,daSize(da) * daType(da));
    return buffer;
}

void daBzero(void * da)
{
    memset(da, '\0', daCap(da));
    *daField(da, SIZE) = 0;
}

#endif // DA_IMPLEMENTATION
