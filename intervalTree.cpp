struct Node{
    Node():totalSum(0),left(nullptr),right(nullptr),leftSide(-1),rightSide(-1)
    {}
    int totalSum;
    Node*left;
    Node*right;
    int leftSide,rightSide;//[leftSide,rightSide]
};
int recursionBuild(Node* &root,const vector<int> &vec,int left,int right)
{
    if(left>right)
    {
        return 0;
    }
    else if(left==right)
    {
        root=new Node;
        root->left=nullptr;
        root->right=nullptr;
        root->leftSide=root->rightSide=left;
        root->totalSum=vec[left];
        return root->totalSum;
    }
    else
    {
        root=new Node;
        root->leftSide=left;
        root->rightSide=right;
        int mid=(right+left)/2;
        root->totalSum=recursionBuild(root->left,vec,left,mid)+recursionBuild(root->right,vec,mid+1,right);
        return root->totalSum;
    }
}

Node* buildIntervalTree(const vector<int> &vec)
{
    cout<<__FUNCTION__<<endl;
    if(vec.size()==0)
        return nullptr;
    if(vec.size()==1)
    {
        Node *root=new Node;
        root->leftSide=0;
        root->rightSide=vec.size()-1;
        root->left=nullptr;
        root->right=nullptr;
        root->totalSum=vec[0];
        return root;
    }
    Node *root=new Node;
    root->leftSide=0;
    root->rightSide=vec.size()-1;
    int mid=(vec.size()-1)/2;
    root->totalSum=recursionBuild(root->left,vec,0,mid)+recursionBuild(root->right,vec,mid+1,root->rightSide);
    return root;
}
int select(Node*root,int left,int right)
{
    if(left==root->leftSide&&right==root->rightSide)
        return root->totalSum;
    else
    {
        int mid=(root->leftSide+root->rightSide)/2;
        if(right<=mid)
            return select(root->left,left,right);
        else if(left>mid)
            return select(root->right,left,right);
        else if(left<=mid&&right>mid)
            return select(root->left,left,mid)+select(root->right,mid+1,right);
    }
}
void change(Node*root,int No,int value)
{
    if(root->leftSide==No&&root->rightSide==No)
    {
        root->totalSum+=value;
        return;
    }
    else
    {
        root->totalSum+=value;
        int mid=(root->leftSide+root->rightSide)/2;
        if(No<=mid)
            change(root->left,No,value);
        else
            change(root->right,No,value);
    }
}

void travel(Node *root)
{

    if(root)
    {
        cout<<"["<<root->leftSide<<","<<root->rightSide<<"]"<<" :"<<root->totalSum<<endl;
        travel(root->left);
        travel(root->right);
    }
}
