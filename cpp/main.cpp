#include <bits/stdc++.h>
using namespace std;

const int mod = 10008;
const int maxn = 1e5 + 5;
int a[maxn];
long long dp[maxn][10];

int main(int argc, char const *argv[])
{
    int T;
    cin >> T;
    while (T--)
    {
        string s;
        cin >> s;
        int len = s.length();
        memset(dp, 0, sizeof(dp));
        for (size_t i = 0; i < len; i++)
        {
            a[i] = s[i] - '0';
            if (a[i] % 2 == 1)
            {
                dp[i + 1][2] += 1;
            }
            if (a[i] % 4 == 0)
            {
                dp[i + 1][0] += 1;
            }
        }
        long long sum = 0;
        for (size_t i = 0; i < len; i++)
        {
            if(a[i]==4||a[i]==8)
            {
                sum+=i+1;
            }
            else if(a[i]==2)
            {
                if(dp[i][2]==1)
                {
                    sum+=i;
                }
            }
            else if(a[i]==0)
            {
                if(dp[i][0]==1)
                {
                    sum+=i;
                }
                sum+=1;
            }
            sum%=mod;
        }
        cout<<sum<<endl;
    }
    return 0;
}
