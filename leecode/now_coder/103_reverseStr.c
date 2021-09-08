char* solve(char* str)
{
    int len = strlen(str);
    char *newstr = (char *)malloc(len);

    for (int i = 0; i < len; i++) {
        newstr[i] = str[len - i - 1];
    }

    return newstr;
}