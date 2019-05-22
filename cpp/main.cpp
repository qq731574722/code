#include <stdio.h>

struct A
{
    char a;
    long b;
    char c;
    double d;
};

struct B
{
    char a;
    char c;
    long b;
    double d;
};


int main(int argc, char const *argv[])
{
    A a;
    printf("%u\n",sizeof(a));
    printf("%x\n",&a.a);
    printf("%x\n",&a.b);
    printf("%x\n",&a.c);
    printf("%x\n",&a.d);
    B b;
    printf("%u\n",sizeof(b));
    printf("%x\n",&b.a);
    printf("%x\n",&b.b);
    printf("%x\n",&b.c);
    printf("%x\n",&b.d);
    return 0;
}
