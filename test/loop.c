int a[10];
int x;
void output(int out)
{
    ;
}
void xx(void)
{
    x = x + 3;
}
int main(void)
{
    int i;
    i = 0;
    x = 1;
    while (i <= 9)
    {
        a[i] = x;
        i = i + 1;
        xx();
    }
    while(i<=9)
    {
        output(a[i]);
    }
    return 0;
}