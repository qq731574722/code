#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
    //freopen("data/6.in","r",stdin);
    //freopen("data/6.out","w",stdout);
    int n, a, b;
    scanf("%d",&n);
    for (size_t i = 0; i < n; i++)
    {
        if(i==0)
            scanf("%d",&a);
        else
        {
            scanf("%d",&b);
            a^=b;
        }
    }
    printf("%d\n",a);
    return 0;
}
