#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 5;

int a[maxn],
    b[maxn],
    pre[maxn],  //记录a数组的前缀最大值
    post[maxn]; //记录b数组的后缀最大值

vector<int> ans;

int main(int argc, char const *argv[])
{
    int N;
    //freopen("data/7.in", "r", stdin);
    //freopen("data/7.out", "w", stdout);
    scanf("%d", &N);
    for (size_t i = 1; i <= N; i++)
        scanf("%d", a + i);
    for (size_t i = 1; i <= N; i++)
        scanf("%d", b + i);
    pre[0] = -1;
    for (size_t i = 1; i <= N; i++)
    {
        if (a[i] < pre[i - 1])
            pre[i] = pre[i - 1];
        else
            pre[i] = a[i];
    }
    post[N + 1] = -1;
    for (size_t i = N; i >= 1; i--)
    {
        if (b[i] < post[i + 1])
            post[i] = post[i + 1];
        else
            post[i] = b[i];
    }
    for (size_t i = 1; i <= N; i++)
    {
        if (a[i] >= pre[i - 1] && b[i] >= post[i + 1])
            ans.push_back(i);
    }
    int sz = ans.size();
    for (size_t i = 0; i < sz; i++)
    {
        printf("%d", ans[i]);
        if (i != sz - 1)
            printf(" ");
    }
    if (sz == 0)
        printf("none");
    printf("\n");
    return 0;
}
