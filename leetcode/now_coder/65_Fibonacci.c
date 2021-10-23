int Fibonacci(int n ) {
    if (n == 0 || n == 1)
        return n;

    int a = 0, b = 1, c, i;
    for (i = 2; i < n + 1; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    return c;
}
