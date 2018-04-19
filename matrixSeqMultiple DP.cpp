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
#include <sstream>
#include <stack>
using namespace std;
//矩阵链乘法
//min_mul[N]=min(min_mul[N-1]+times(1*2..N-1,N),
//                min_mul[N-2]+times(1*2...N-2,N-1*N))
#define MAX_MATRIX 1000000
struct matrix{
    matrix(int M,int N):M(M),N(N){}
  int M;
  int N;
};
struct Node{
    Node():min_times(-1),state(-1){}
  int min_times;
  int state;//0 single,1 pair
};
Node min_mul[MAX_MATRIX];
int times(const matrix&a,const matrix&b)
{
    return a.M*a.N*b.N;
}
int seqMatrixMul(const vector<matrix>&matrix_list)
{
    min_mul[0].min_times=0;
    min_mul[1].min_times=times(matrix_list[0],matrix_list[1]);
    for(int i=2;i<matrix_list.size();i++)
    {
        int pre=min_mul[i-1].min_times+times(matrix(matrix_list[0].M,matrix_list[i-1].N),matrix_list[i]);
        int nex=min_mul[i-2].min_times+times(matrix(matrix_list[0].M,matrix_list[i-2].N),matrix(matrix_list[i-1].M,matrix_list[i].N));
        min_mul[i].min_times=std::min(pre,nex);
        if(min_mul[i].min_times==pre)
            min_mul[i].state=0;
        else
            min_mul[i].state=1;
    }
    return min_mul[matrix_list.size()-1].min_times;
}
int main()
{
    vector<matrix> vec;
    vec.push_back(matrix(10,100));
    vec.push_back(matrix(100,5));
    vec.push_back(matrix(5,50));
    vec.push_back(matrix(50,30));
    vec.push_back(matrix(30,200));
    vec.push_back(matrix(200,45));
    vec.push_back(matrix(45,55));
    vec.push_back(matrix(55,5));
    vec.push_back(matrix(5,456));
    vec.push_back(matrix(456,4));
    cout<<"min times:"<<seqMatrixMul(vec)<<endl;
    int j=vec.size()-1;
    int times_left=0;
    stack<string> res;
    while(j>=0)
    {
        if(j==0)
        {
            stringstream ss;
            ss<<j;
            res.push(ss.str());
            res.push("(");
            break;
        }
        else if(j==1)
        {
            stringstream s1,s2;
            s1<<j;
            s2<<j-1;
            res.push(s1.str());
            res.push(s2.str());
            res.push("(");
            break;
        }
        if(min_mul[j].state==0)
        {
            stringstream ss;
            ss<<j;
            res.push(ss.str());
            res.push(")");
            j-=1;
        }
        else
        {
            stringstream s1,s2;
            s1<<j;
            s2<<j-1;
            res.push(")");
            res.push(s1.str());
            res.push(s2.str());
            res.push("(");
            res.push(")");


            j-=2;
            if(j!=1)
                times_left++;
        }
    }
    while(times_left-->0)
        res.push("(");
    while(!res.empty())
    {
        cout<<res.top();
        res.pop();

    }
    cout<<endl;
}
