int x;
int factorial(int n, int ab)
{
    int i;
    i = 6;
    while (i != 0)
    {
        i = i - 1;
    }
    if (n == 1)
    {
        i = i + 1;
        return 1;
    }
    else
        return (n * factorial(n - 1));
}
int y;
int main(void)
{
    int a;
    a = 4;
    a = factorial(a);
    return a;
}