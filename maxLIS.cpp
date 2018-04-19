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
#define MAX_LIST 10000000+1
struct Node{
    Node():max_value(0),mark(-1),lastState(-1){}
    int max_value;
    int mark;
    int lastState;
};
//最长递增子序列
//        max(LIS[i])+1,a[i]<=a[j]&&i<j
//LIS[j]=
//        LIS(j-1)
Node maxLIS[MAX_LIST];
int max_LIS(const vector<int>&A)
{
    maxLIS[0].max_value=1;
    maxLIS[0].mark=0;
    for(int j=1;j<A.size();j++)
    {
        for(int i=0;i<j;i++)
        {
            if(A[i]<=A[j]&&maxLIS[j].max_value<maxLIS[i].max_value+1)
            {
                maxLIS[j].max_value=maxLIS[i].max_value+1;
                maxLIS[j].mark=j;
                maxLIS[j].lastState=i;
            }
        }
        if(maxLIS[j].max_value<maxLIS[j-1].max_value)
        {
            maxLIS[j].max_value=maxLIS[j-1].max_value;
            maxLIS[j].mark=-1;
            maxLIS[j].lastState=j-1;
        }
    }
    return maxLIS[A.size()-1].max_value;
}
int main()
{
    vector<int> vec={1,2,6,4,5,7,3};
    cout<<"max LIS length:"<<max_LIS(vec)<<endl;
    int j=vec.size()-1;
    while(j>=0)
    {
        if(maxLIS[j].mark!=-1)
            cout<<vec[maxLIS[j].mark]<<" ";
        j=maxLIS[j].lastState;
    }
    cout<<endl;
}
