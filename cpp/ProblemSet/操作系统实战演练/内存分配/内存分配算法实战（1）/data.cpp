#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
    freopen("test4.in","w",stdout);
    srand(time(0));
    printf("500 2048 1000\n");
    int addr = 0x0af38c; 
    for (size_t i = 0; i < 500; i++)
    {
        printf("%06x\n",addr);
        addr+=2048;
    }
    for (size_t i = 0; i < 1000; i++)
    {
        int size=rand()%2048+1;
        printf("%d\n",size);
    }
    return 0;
}
