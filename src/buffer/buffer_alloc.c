#include <buffer/buffer_alloc.h>
#include <system/system.h>

#define HEAP_BUFFER_LENGTH  512
static char HEAP_BUFFER[HEAP_BUFFER_LENGTH];
static memory_header *heap;

void buffer_alloc_init();
void buffer_header_init();
void *buffer_alloc(void *ptr, size_t len);
void buffer_realloc(void *ptr);
int verify_header(memory_header *header);

void *buffer_malloc(size_t n, size_t size)
{
    memory_header *cursor = heap;
    memory_header *header = cursor->next;
    void *ret = NULL;

    size_t len = n * size;

    if(cursor == NULL && header == NULL)
    {
        buffer_header_init();
        cursor = heap;
    }
    else if(cursor == NULL)
    {
        cursor = header;
        cursor->size = (void *)cursor - (void*)HEAP_BUFFER;
    }


    if(n != 0 && (len/n) != size)
        ret = NULL;
    else
    {
        size_t len_alloc = sizeof(memory_header) + len;
        while(cursor != NULL)
        {
            if(cursor->size > len_alloc && cursor->alloc == 0)
            {
                ret = buffer_alloc(cursor, len);
                break;
            }
            cursor = cursor->next;
        }
    }
    return ret;
}

void *buffer_alloc(void *ptr, size_t len)
{
    memory_header *cursor = ptr;
    memory_header *header = NULL;
    void *ret = NULL;

    cursor->alloc = 1;
    cursor->size = len + sizeof(memory_header);

    header = cursor->next;
    if(header == NULL)
    {
        header = (memory_header *)((void*)cursor + cursor->size);
        header->next = NULL;
        header->alloc = 0;
        size_t pOffset = (void*)cursor - (void*)heap;
        header->size = HEAP_BUFFER_LENGTH - cursor->size - pOffset;
        header->prev = cursor;
        cursor->next = header;
    }
    else
    {
        header->prev = cursor;
        cursor->next = header;
    }

    ret = (void *)cursor + sizeof(memory_header);

    return ret;
}

void buffer_free(void *ptr)
{
    memory_header *cursor = ptr;
    cursor = (memory_header*)((void*)cursor - sizeof(memory_header));

    if(verify_header(cursor) != 0)
    {
        error("buffer_free unlocated");
    }
    else
    {
        cursor->alloc = 0;
        buffer_realloc(cursor);
    }
}

void buffer_realloc(void *ptr)
{
    memory_header *cursor = ptr;
    memory_header *header = NULL;
    size_t pOffset = 0;

    while(cursor != NULL)
    {
        header = cursor->prev;
        if(header != NULL && header->alloc == 0)
        {
            if(cursor->alloc == 0)
            {
                pOffset = (void*)cursor - (void *)header + cursor->size;
                header->size = pOffset;
                header->next = cursor->next;
                cursor->next = header;
            }
        }

        cursor = cursor->next;
    }
}
void buffer_alloc_init()
{
    memset(&HEAP_BUFFER, 0, HEAP_BUFFER_LENGTH);
    buffer_header_init();

}

void buffer_header_init()
{
    printf("HEAP_BUFFER %p\r\n", HEAP_BUFFER);
    memset(&HEAP_BUFFER, 0, sizeof(memory_header));
    memory_header *header = (memory_header *)HEAP_BUFFER;
    header->alloc = 0;
    header->size = HEAP_BUFFER_LENGTH - sizeof(memory_header);
    header->prev = NULL;
    header->next = 0;

    heap = (memory_header *)HEAP_BUFFER;
}

void display_all_header()
{
    printf("DISPLAY ALL HEADER\r\n");
    memory_header *cursor = heap;

    while(cursor != NULL)
    {
        display_header(cursor);

        cursor = cursor->next;
    }
}

void display_header(memory_header *header)
{
    printf("\tADDRESS: %08x   \tPREV: %08x  \tNEXT: %08x    \tALLOC: %d   \tSIZE: %d\r\n",
           header, header->prev, header->next, header->alloc, header->size);
}

int verify_header(memory_header *header)
{
    int result = 0;

    if(header == NULL)
        result = 1;

    if(header->alloc > 1)
        result = 1;

    if(header->prev == header->next)
        result = 1;

    if((header < HEAP_BUFFER) || (header > HEAP_BUFFER + HEAP_BUFFER_LENGTH))
        result = 1;

    return result;
}

