void output(int out)
{
    ;
}
int factorial(int n)
{
    int res;
    if (n == 1)
    {
        res = 1;
    }
    else
    {
        res = n * factorial(n - 1);
    }
    output(res);
    return res;
}
int main(void)
{
    int a;
    a = 4;
    a = factorial(a);
    return 0;
}