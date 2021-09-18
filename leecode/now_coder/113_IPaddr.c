#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

bool check_IPv4(char *IP, char *next)
{
    if (IP[0] == '0') {
        if (IP[1])
            return false;
    }

    errno = 0;
    char *end;
    long num = strtol(IP, &end, 10);
    if (errno)
        return false;

    if (end != next)
        return false;

    if (end == IP)
        // no number
        return false;

    if (num < 0 || num > 255)
        return false;

    return true;
}

bool validIPv4(char *IP)
{
    char *end = IP + strlen(IP);

    for (int i = 0; i < 3; i++) {
        char *next = strstr(IP, ".");
        if (next == NULL)
            return false;

        *next = 0;
        if (check_IPv4(IP, next) == false)
            return false;
        IP = next + 1;
    }

    return check_IPv4(IP, end);
}

bool check_IPv6(char *IP, char *next)
{
    errno = 0;
    char *end;
    long num = strtol(IP, &end, 16);
    if (errno)
        return false;

    if (end != next)
        return false;

    int width = end - IP;
    if (width < 1 || width > 4)
        // no number
        return false;

    return true;
}

bool validIPv6(char *IP)
{
    char *end = IP + strlen(IP);

    for (int i = 0; i < 7; i++) {
        char *next = strstr(IP, ":");
        if (next == NULL)
            return false;

        *next = 0;
        if (check_IPv6(IP, next) == false)
            return false;
        IP = next + 1;
    }

    return check_IPv6(IP, end);
}

char* solve(char *IP)
{
    char *cp = (char *)malloc(strlen(IP) + 1);
    strcpy(cp, IP);
    
    const char *ret = validIPv4(cp) ? "IPv4" : validIPv6(cp) ? "IPv6" : "Neither";
    return (char *)ret;
}

int main(void)
{
    // char *str = "172.16.254.1";
    // char *str = "2001:0db8:85a3:0:0:8A2E:0370:7334";
    // char *str = "256.256.256.256";
    char *str = "1a1.4.5.6";

    printf("%s\n", solve(str));
    return 0;
}
