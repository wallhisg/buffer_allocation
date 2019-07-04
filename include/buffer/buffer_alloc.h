#ifndef BUFFER_ALLOC_H
#define BUFFER_ALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_DEBUG                1
#define MEMORY_ALIGN_MULTIPLE       4

#define GCC 	1

#if GCC
    #define MEMORY_ALIGN_MULTIPLE   8   //  4 ~ cpu 32 bit
#elif GCC_AVR                           //  8 ~ cpu 64 bit
    #define MEMORY_ALIGN_MULTIPLE   2   //  cpu 8 bit
#elif GCC_XTENSA
    #define MEMORY_ALIGN_MULTIPLE   4   //  cpu 32 bit
#endif


typedef struct _memory_header {
    struct _memory_header *prev;
    size_t alloc;
    size_t size;
    struct _memory_header *next;
} memory_header;

void *buffer_malloc(const size_t size);
void buffer_free(void *ptr);


void display_heap();

#endif // BUFFER_ALLOC_H

