#include "securec.h"
#include <string.h>

#define BUFFER_SIZE 40

int main(void)
{
    char buffer[BUFFER_SIZE] = "This is a test of the memset function";
    errno_t rc = EOK;

    printf("Before: %s\n", buffer);
    rc = memset_s(buffer, BUFFER_SIZE, '*', 20);
    printf("After: rc = %d, %s\n", rc, buffer);

    /* count is bigger than destMax, return ERANGE_AND_RESET and destMax size is set. */
    rc = memset_s(buffer, BUFFER_SIZE, '*', BUFFER_SIZE + 1);
    printf("Later: rc = %d, %s\n", rc, buffer);

    return 0;
}
