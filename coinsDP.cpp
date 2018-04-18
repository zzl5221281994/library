#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <memory>
#include <future>
#include <functional>
#include <utility>
#include <algorithm>
#include <type_traits>
using namespace std;
//k种面值的硬币，给出total，用最少硬币数得出total
//sum[total] 代表给出total的最小硬币数
//sum[total]=min(sum[total-coin[0]],sum[total-coin[1]]...sum[total-coin[k]])+1
struct Node{
    Node():coins(INT_MAX),lastState(-1),addCoins(-1){}
    int coins;
    int lastState;
    int addCoins;
};
#define MAX_TOTAL 1000000
Node sum[MAX_TOTAL];
void minCoins(int total,const std::vector<int>&coins)
{
    //std::sort(coins.begin(),coins.end());
    sum[0].coins=0;
    for(int j=1;j<=total;j++)
        for(int i=0;i<coins.size();i++)
            if(j-coins[i]>=0&&sum[j-coins[i]].coins+1<sum[j].coins)
            {
                //cout<<j-coins[i]<<":"<<sum[j-coins[i]].coins+1<<":"<<sum[j].coins<<endl;
                sum[j].coins=sum[j-coins[i]].coins+1;
                sum[j].addCoins=coins[i];
                sum[j].lastState=j-coins[i];
            }
}
int main()
{
    std::vector<int> coins={1,2,5};
    int total=20;
    minCoins(total,coins);
    cout<<"min coins num:"<<sum[total].coins<<endl;

    while(sum[total].coins<INT_MAX&&total>0)
    {
        cout<<sum[total].addCoins<<endl;
        total-=sum[total].addCoins;
    }
}
