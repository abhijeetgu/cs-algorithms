#include<iostream>
using namespace std;

void buildTree(int *tree,int *a,int index,int s,int e)
{
    //Base case
    if(s>e)
    {
        return;
    }
    //Base Case -leaf node
    if(s==e)
    {
        tree[index]=a[s];
        return;
    }
    //Recursive case
    int mid=(s+e)/2;
    //left sub-tree
    buildTree(tree,a,2*index,s,mid);
    //right subtree
    buildTree(tree,a,2*index+1,mid+1,e);

    int left=tree[index*2];
    int right =tree[2*index+1];

    tree[index]=min(left,right);
}
//Return a min elsement from the tree lying in range qs and qe
int query(int *tree,int index,int s,int e,int qs,int qe)
{
    //3 cases

    //1.no overlap
    if(qs>e || qe<s)
    {
        return INT_MAX;
    }

    //2. complete overlap
    if(s>=qs && e<=qe)
    {
        return tree[index];
    }

    //3. partial overlap-call both sides
    int mid=(s+e)/2;
    int leftAns=query(tree,2*index,s,mid,qs,qe);
    int rightAns=query(tree,2*index+1,mid+1,e,qs,qe);

    return min(leftAns,rightAns);
}
void updateNode(int *tree,int index,int s,int e,int i,int value)
{
    //No Overlap
    if(i<s || i>e)
    {
        return;
    }
    //reached leaf node
    if(s==e)
    {
        tree[index]=value;
        return;
    }
    //Lying in Range -i is lying between s and e
    int mid=(s+e)/2;
    updateNode(tree,2*index,s,mid,i,value);
    updateNode(tree,2*index+1,mid+1,e,i,value);
    tree[index]=min(tree[2*index],tree[2*index+1]);
    return;
}
//Range Update
//you will be given a range rs and re,
//and you increment every element in the range

void updateRange(int *tree,int index,int s,int e,int rs,int re,int inc)
{
    //No overlap
    if(re<s || rs>e)
    {
        return;
    }
    //Reached leaf Node
    if(s==e)
    {
        tree[index]+=inc;
        return;
    }
    //Lying in Range -Call both sides
    int mid=(s+e)/2;
    updateRange(tree,2*index,s,mid,rs,re,inc);
    updateRange(tree,2*index+1,mid+1,e,rs,re,inc);
    tree[index]=min(tree[2*index],tree[2*index+1]);
    return;
}
int main()
{
    int a[]={1,4,-2,3};
    int n=4;

    int *tree=new int[4*n+1];
    int index=1;
    int s=0;
    int e=n-1;
    buildTree(tree,a,index,s,e);

    int no_of_q;
    cin>>no_of_q;
    //updateNode(tree,1,s,e,2,8);
    updateRange(tree,1,s,e,1,2,4);

    while(no_of_q--)
    {
        int qs,qe;
        cin>>qs>>qe;
        cout<<"Min value between range is";
        cout<<query(tree,1,s,e,qs,qe)<<endl;
    }

    return 0;

}
