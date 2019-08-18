#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
    freopen("6.in", "w", stdout);
    srand(time(0));
    multiset<int> s;
    int n = 400000;
    printf("%d\n", n * 2 + 1);
    for (size_t i = 0; i < n; i++)
    {
        int x = (rand() % 1000000) + 1;
        printf("%d ", x);
        s.insert(x);
    }
    for (size_t i = 100; i < 1000000; i++)
    {
        if (!s.count(i))
        {
            s.insert(i);
            break;
        }
    }
    for (auto &&i : s)
    {
        printf("%d ", i);
    }
    return 0;
}
