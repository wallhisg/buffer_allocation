
#ifndef BUFFER_ALLOC_H
#define BUFFER_ALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>


typedef struct memory_header{
    struct memory_header *prev;
    size_t size;
    size_t alloc;
    struct memory_header *next;
} memory_header;

void *buffer_malloc(size_t n, size_t size);
void buffer_free(void *ptr);



void display_all_header();
void display_header(memory_header *header);

#endif // BUFFER_ALLOC_H

