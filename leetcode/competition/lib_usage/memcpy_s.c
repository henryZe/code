#include "securec.h"
#include <string.h>

#define BUFFER_SIZE 11

int main(void)
{
    char str1[BUFFER_SIZE] = "0123456789";
    char str2[BUFFER_SIZE] = {0x00};
    errno_t rc = EOK;

    rc = memcpy_s(str2, BUFFER_SIZE, str1, BUFFER_SIZE - 1);
    printf("rc = %d, %s\n", rc, str2);

    /* count is bigger than destMax, return ERANGE_AND_RESET and dest is reset. */
    rc = memcpy_s(str2, BUFFER_SIZE, str1, BUFFER_SIZE + 1);
    printf("rc = %d, %s\n", rc, str2);

    /* initialize */
    rc = memcpy_s(str2, BUFFER_SIZE, str1, BUFFER_SIZE - 1);
    printf("rc = %d, %s\n", rc, str2);

    /* overlap, return EOVERLAP_AND_RESET and dest is reset. */
    rc = memcpy_s(str2, BUFFER_SIZE, str2 + 2, BUFFER_SIZE - 1);
    printf("rc = %d, %s\n", rc, str2);

    return 0;
}
