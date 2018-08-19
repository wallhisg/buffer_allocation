#include <buffer/buffer_alloc.h>

int main()
{
    printf("SIZEO OF  MEMORY HEADER: %lu\r\n", sizeof(memory_header));

    char *str1  = (char *)buffer_malloc(0x10 * sizeof(char));
    char *str2  = (char *)buffer_malloc(0x10 * sizeof(char));
    display_heap();

    buffer_free(str1);
    buffer_free(str2);
    display_heap();
}
