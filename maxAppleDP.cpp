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
//map[M+1][N+1]，其中每个格子有一定量的苹果，
//现从map[1][1]出发，每次向下或者向右走一步，并拾取对应格子的苹果
//问走到map[M][N]最多能拾取多少个苹果
//max_apple[M][N]=max(max_apple[M-1][N],max_apple[M][N-1])+map[M][N]

struct Node{
    Node():currentTotal(0),lastStep(-1){}
    int currentTotal;
    int lastStep;
};
void maxApple(vector<vector<Node>>&max_apple, vector<vector<int>>&map,int N,int M)//(M+1)*(N+1)
{
    cout<<__FUNCTION__<<endl;
    max_apple[1][1].currentTotal=map[1-1][1-1];
    //cout<<"QQ"<<endl;
    for(int i=2;i<=N;i++)
    {
        max_apple[1][i].currentTotal=max_apple[1][i-1].currentTotal+map[1-1][i-1];
        max_apple[1][i].lastStep=0;
    }
    //cout<<"F"<<endl;
    for(int i=2;i<=M;i++)
    {
        max_apple[i][1].currentTotal=max_apple[i-1][1].currentTotal+map[i-1][1-1];
        max_apple[i][1].lastStep=1;
    }
    //cout<<"DE"<<endl;
    for(int i=2;i<=M;i++)
        for(int j=2;j<=N;j++)
        {
            int maxVal=std::max(max_apple[i-1][j].currentTotal,max_apple[i][j-1].currentTotal);
            max_apple[i][j].currentTotal=maxVal+map[i-1][j-1];
            if(maxVal==max_apple[i-1][j].currentTotal)
                max_apple[i][j].lastStep=1;
            else
                max_apple[i][j].lastStep=0;
        }
}
int main()
{
     vector<vector<int>> map={{4,6,3},{5,8,9},{7,11,10}};
     vector<vector<Node>> max_apple(4);
     for(int i=0;i<4;i++)
         for(int j=0;j<4;j++)
             max_apple[i].push_back(Node());
    maxApple(max_apple,map,3,3);
    cout<<"max apple nums:"<<max_apple[3][3].currentTotal<<endl;
    int i=3,j=3;
    while(max_apple[i][j].lastStep!=-1)
    {
        cout<<i<<" "<<j<<endl;
        if(max_apple[i][j].lastStep==0)
            j-=1;
        else
            i-=1;
    }
}
