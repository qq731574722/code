#include <bits/stdc++.h>

using namespace std;

struct mem_info
{
    unsigned start; //起始地址
    unsigned size;  //大小
};

list<mem_info> free_mem_list;

int first_fit(unsigned size)
{
    while (size % 4)
        size++;
    size_t len = free_mem_list.size();
    for (auto &&i : free_mem_list)
    {
        if (i.size >= size)
        {
            unsigned res = i.start;
            i.start += size;
            i.size -= size;
            return res;
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    //freopen("test4.in","r",stdin);
    //freopen("test4.out","w",stdout);
    unsigned N, Y, M;
    scanf("%u%u%u", &N, &Y, &M);
    for (size_t i = 0; i < N; i++)
    {
        unsigned st;
        scanf("%x", &st);
        free_mem_list.push_back(mem_info{st, Y});
    }
    for (size_t i = 0; i < M; i++)
    {
        unsigned size;
        scanf("%u", &size);
        int res = first_fit(size);
        if(res==-1)
            printf("not enough memory!\n");
        else
            printf("%06x\n",res);
    }
    return 0;
}
