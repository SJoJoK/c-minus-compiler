int a[10];
int x;
void output(int out)
{
    ;
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
        x = x + 3;
    }
    i = 0;
    while (i <= 9)
    {
        output(a[i]);
        i = i + 1;
    }
    return 0;
}