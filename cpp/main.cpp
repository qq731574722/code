#include <bits/stdc++.h>

using namespace std;

struct Rank
{
    int level;
    int star;
};

void add(Rank &r)
{
    r.star++;
    if (r.level >= 21 && r.level <= 25 && r.star == 3)
    {
        r.star = 1;
        r.level--;
    }
    else if (r.level >= 16 && r.level <= 20 && r.star == 4)
    {
        r.star = 1;
        r.level--;
    }
    else if (r.level >= 11 && r.level <= 15 && r.star == 5)
    {
        r.star = 1;
        r.level--;
    }
    else if (r.level >= 1 && r.level <= 10 && r.star == 6)
    {
        r.star = 1;
        r.level--;
    }
}

void sub(Rank &r)
{
    if (r.star == 0 && r.level == 25)
        return;
    r.star--;
    if (r.star >= 0)
        return;
    if (r.level >= 20 && r.level <= 24)
    {
        r.star = 1;
        r.level++;
    }
    else if (r.level >= 15 && r.level <= 21)
    {
        r.star = 2;
        r.level++;
    }
    else if (r.level >= 10 && r.level <= 14)
    {
        r.star = 3;
        r.level++;
    }
    else if (r.level >= 1 && r.level <= 9)
    {
        r.star = 4;
        r.level++;
    }
}

int solve(string str)
{
    Rank rank;
    rank.level = 25;
    rank.star = 0;
    int win_cnt = 0;
    for (auto i : str)
    {
        if (i == 'W')
        {
            win_cnt++;
            if (win_cnt >= 3 && rank.level >= 6)
                add(rank);
            add(rank);
            if (rank.level == 0)
                return 0;
        }
        else if (i == 'L')
        {
            win_cnt = 0;
            if (rank.level < 20 || (rank.level == 20 && rank.star > 0))
                sub(rank);
        }
    }
    return rank.level;
}

int main(int argc, char const *argv[])
{
    string str;
    while (cin >> str)
    {
        int res = solve(str);
        if (res == 0)
            cout << "Legend" << endl;
        else
            cout << res << endl;
    }
    return 0;
}
