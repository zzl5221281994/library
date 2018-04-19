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
#define MAX_M 10000
#define MAX_N 10000
struct Node
{
    Node():lcs(0),lastState(-1),choose(-1){}
    int lcs;
    int lastState;//0 左,1 上,2 左上
    char choose;
};
Node maxLCS[MAX_M+1][MAX_N+1];
//LCS
//                maxLCS[M-1,N-1]+1,if(S[M]==T[N])
//maxLCS[M,N]=
//                max(maxLCS[M-1,N],maxLCS[M,N-1],maxLCS[M-1][N-1]) else
int min_eidt(const string &S,const string &T)
{
    if(S.size()==0)
        return 0;
    if(T.size()==0)
        return 0;
    if(S[0]==T[0])
    {
        maxLCS[1][1].lcs=1;
        maxLCS[1][1].choose=S[0];
    }
    else
        maxLCS[1][1].lcs=0;
    for(int i=2;i<=T.size();i++)
    {
        maxLCS[1][i].lcs=maxLCS[1][1].lcs;
        maxLCS[1][i].lastState=0;
    }
    for(int i=2;i<=S.size();i++)
    {
        maxLCS[i][1].lcs=maxLCS[1][1].lcs;
        maxLCS[i][1].lastState=1;
    }

    for(int i=2;i<=S.size();i++)
        for(int j=2;j<=T.size();j++)
            if(S[i-1]==T[j-1])
            {
                maxLCS[i][j].lcs=maxLCS[i-1][j-1].lcs+1;
                maxLCS[i][j].choose=S[i-1];
                maxLCS[i][j].lastState=2;

            }
            else
            {
                maxLCS[i][j].lcs=std::max(std::max(maxLCS[i-1][j].lcs,maxLCS[i][j-1].lcs),maxLCS[i-1][j-1].lcs);
                if(maxLCS[i][j].lcs==maxLCS[i-1][j].lcs)
                {
                    maxLCS[i][j].lastState=1;
                }
                else if(maxLCS[i][j].lcs==maxLCS[i][j-1].lcs)
                {
                    maxLCS[i][j].lastState=0;
                }
                else if(maxLCS[i][j].lcs==maxLCS[i-1][j-1].lcs)
                {
                    maxLCS[i][j].lastState=2;
                }
            }
    return maxLCS[S.size()][T.size()].lcs;
}
int main()
{
    string str1="qwets",str2="qetrts";
    cout<<min_eidt(str1,str2)<<endl;
    int m=str1.size(),n=str2.size();
    while(m>=1&&n>=1)
    {
        //cout<<m<<":"<<n<<":"<<maxLCS[m][n].lastState<<endl;
        if(maxLCS[m][n].choose!=-1)
            cout<<maxLCS[m][n].choose;
        if(maxLCS[m][n].lastState==-1&&m==1&&n==1)
            break;
        if(maxLCS[m][n].lastState==0)
        {
            n-=1;
        }
        else if(maxLCS[m][n].lastState==1)
        {
            m-=1;
        }
        else if(maxLCS[m][n].lastState==2)
        {
            m-=1;
            n-=1;
        }
    }
}
