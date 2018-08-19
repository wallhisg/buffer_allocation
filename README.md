# Buffer allocation
Buffer_allocation is simple memory allocation.

Replace malloc and free in c with static memory.

Size of the static heap can change by **HEAP_BUFFER_CONFIG_LENGTH**

Using for the microcontrollers (PIC, AVR).

# Features:
Simple.

No dependencies.

No dynamic memory allocation.

API has only 2 functions

*- buffer_malloc*

*- buffer_free*

# Example

char *str1  = (char *)buffer_malloc(0x10 * sizeof(char));

buffer_free(str1);