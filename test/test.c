int factorial(int n)
{
    if (n == 1)
        return 1;
    else
        return (n * factorial(n - 1));
}
int main(void)
{
    int a;
    a = 4;
    a = factorial(a);
    return a;
}