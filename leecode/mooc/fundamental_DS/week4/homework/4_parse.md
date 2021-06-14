
~~~ C
// A is order array
// T is result tree
void solve(int ALeft, int ARight, int TRoot)
{
    n = ARight - ALeft + 1;
    if (!n)
        return;

    L = GetLeftLength(n);
    T[TRoot] = A[ALeft + L];
    LeftTRoot = TRoot * 2 + 1;
    RightTRoot = LeftTRoot + 1;

    solve(ALeft, ALeft + L - 1, LeftTRoot);
    solve(ALeft + L + 1, ARight, RightTRoot);
}
~~~
