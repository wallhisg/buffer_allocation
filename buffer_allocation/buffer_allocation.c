#include <buffer/buffer_alloc.h>

int main()
{
    printf("SIZEO OF  MEMORY HEADER: %d\r\n", sizeof(memory_header));

    buffer_alloc_init();
    char *str1 = (char*)buffer_malloc(0x31, sizeof(char));
    memset(str1, 0, 0x31);
    memcpy(str1, "STR1\r\n", 6);
    printf("STR1: %s\r\n", str1);
    char *str2 = (char*)buffer_malloc(0x32, sizeof(char));
    memset(str2, 0, 0x32);
    memcpy(str2, "STR2\r\n", 6);
    printf("STR2: %s\r\n", str2);
    char *str3 = (char*)buffer_malloc(0x33, sizeof(char));
    memset(str3, 0, 0x33);
    memcpy(str3, "STR3\r\n", 6);
    printf("STR3: %s\r\n", str3);
//    char *str4 = (char*)buffer_malloc(0x34, sizeof(char));
    display_all_header();

    buffer_free(str1);
    display_all_header();

    buffer_free(str2);
    display_all_header();

    buffer_free(str3);
    display_all_header();
}
