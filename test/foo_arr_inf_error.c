int foo(void)
{
    ;
}
void bar(void)
{
    return;
}
int main(void)
{
    int a;
    int b[10];
    int c;
    a = 0;
    a[1] = 0;
    b[bar()] = 0;
    if (a < bar())
    {
        a + bar();
        a = bar();
    }
    return a;
}