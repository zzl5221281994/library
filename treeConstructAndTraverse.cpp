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
#include <map>
#include <unordered_map>
using namespace std;
template<typename T>
void printVec(const vector<T>&vec)
{
    cout<<__FUNCTION__<<endl;
    for(auto &c:vec)
        cout<<c<<" ";
    cout<<endl;
}
template<typename T>
struct Node{
    Node():left(nullptr),right(nullptr){}
    Node*left;
    Node*right;
    T data;
};
template<typename T>
Node<T>* constructFromPreInOrder(const vector<T>&pre,const vector<T>&in)
{
    cout<<__FUNCTION__<<endl;
    if(pre.empty()||in.empty())
        return nullptr;
    Node<T>*root=new Node<T>;
    root->data=pre[0];
    auto pos=find(in.begin(),in.end(),pre[0]);
    vector<T> inLeft,inRight;
    vector<T> preLeft,preRight;
    if(pos!=in.begin())
    {
        inLeft.assign(in.begin(),pos);
        preLeft.assign(pre.begin()+1,pre.begin()+1+inLeft.size());
    }
    if(pos!=in.end()-1)
    {
        inRight.assign(pos+1,in.end());
        preRight.assign(pre.begin()+1+inLeft.size(),pre.end());
    }
    root->left=constructFromPreInOrder(preLeft,inLeft);
    root->right=constructFromPreInOrder(preRight,inRight);
    return root;
}
template<typename T>
Node<T>* constructFromPostInOrder(const vector<T>&post,const vector<T>&in)
{
    return;
}
template<typename T>
void travelPreOrderRecursion(Node<T>*root)
{
    //cout<<__FUNCTION__<<endl;
    if(root==nullptr)
        return;
    cout<<root->data<<" ";
    travelPreOrder(root->left);
    travelPreOrder(root->right);
}
template<typename T>
void travelInOrderRecursion(Node<T>*root)
{
    //cout<<__FUNCTION__<<endl;
    if(root==nullptr)
        return;
    travelInOrder(root->left);
    cout<<root->data<<" ";
    travelInOrder(root->right);
}
template<typename T>
void travelPostOrderRecursion(Node<T>*root)
{
    //cout<<__FUNCTION__<<endl;
    if(root==nullptr)
        return;
    travelPostOrder(root->left);
    travelPostOrder(root->right);
    cout<<root->data<<" ";
}
template<typename T>
void travelInOrder(Node<T>*root)
{
    if(root==nullptr)
        return;
    stack<Node<T>*> s;
    Node<T>*temp=root;
    while(temp!=nullptr||!s.empty())
    {
        if(temp!=nullptr)
        {
            s.push(temp);
            temp=temp->left;
        }
        else
        {
            temp=s.top();
            cout<<temp->data<<" ";
            s.pop();
            temp=temp->right;
        }
    }
    cout<<endl;
}
template<typename T>
void travelPreOrder(Node<T>*root)
{
    if(root==nullptr)
        return;
    stack<Node<T>*> s;
    Node<T>*temp=root;
    while(temp!=nullptr||!s.empty())
    {
        if(temp!=nullptr)
        {
            cout<<temp->data<<" ";
            s.push(temp);
            temp=temp->left;
        }
        else
        {
            temp=s.top();
            s.pop();
            temp=temp->right;
        }
    }
    cout<<endl;
}
template<typename T>
void travelPostOrder(Node<T>*root)
{
    unordered_map<Node<T>*,int> mark;
    if(root==nullptr)
        return;
    stack<Node<T>*> s;
    Node<T>*temp=root;
    while(temp!=nullptr||!s.empty())
    {
        if(temp!=nullptr)
        {
            if(temp->left==nullptr&&temp->right==nullptr)
            {
                cout<<temp->data<<" ";
                temp=s.top();
            }
            else
            {
                if(mark.count(temp)==0)
                {
                    s.push(temp);
                    mark[temp]=1;
                    temp=temp->left;
                }
                else
                {
                    if(mark[temp]==1)
                    {
                        mark[temp]=2;
                        temp=temp->right;
                    }
                    else
                    {
                        cout<<temp->data<<" ";
                        s.pop();
                        temp=s.empty()?nullptr:s.top();
                    }
                }
            }
        }
        else
        {
            temp=s.top();
        }
    }
}
 int main()
 {
     vector<int> preOrder={1,2,4,5,8,7,3,6};
     vector<int> inOrder={4,2,8,5,7,1,6,3};
     Node<int>*root=constructFromPreInOrder(preOrder,inOrder);
     travelInOrderCursion<int>(root);
     cout<<endl;
     travelPreOrderCursion<int>(root);
     cout<<endl;
     travelPostOrderCursion<int>(root);
     travelInOrder<int>(root);
     travelPreOrder<int>(root);
     travelPostOrder<int>(root);
     cout<<endl;
     return 0;
 }
