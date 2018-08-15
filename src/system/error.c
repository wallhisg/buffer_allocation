#include <system/error.h>

void error(const char* reason)
{
    (void)printf("FATAL: %s\n", reason);
}
