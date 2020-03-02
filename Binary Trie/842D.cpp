// https://codeforces.com/contest/842/problem/D

#include <bits/stdc++.h> 
using namespace std;

const int maxz = (1<<20);
const int maxn = 21;
const int sz = 3e5+5;
int A[sz], done[maxz];

struct node
{
    node* zero;
    node* one;
    node()
    {
        zero = nullptr;
        one = nullptr;
    }
};

node* main_root = nullptr;

node* insert(node* root, int val, int bit)
{
    if(root == nullptr)
    {
        root = new node();
    }
    if(bit >= 0)
    {
        if((val>>bit)&1)
            root -> one = insert(root -> one, val, bit-1);
        else
            root -> zero = insert(root -> zero, val, bit-1);
    }
    return root;
}

int query(node* root, int X, int bit)
{
    if(root == nullptr || bit == -1)
        return 0;
    if((X >> bit) & 1)
    {
        if(root -> one != nullptr)
            return query(root -> one, X, bit-1);
        return (1 << bit) | query(root -> zero, X, bit-1);
    }
    if(root -> zero != nullptr)
        return query(root -> zero, X, bit-1);
    return (1 << bit) | query(root -> one, X, bit-1);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &A[i]);
        done[A[i]]=1;
    }
    
    for(int i=0; i<maxz; i++)
    {
        if(!done[i])
            main_root = insert(main_root, i, maxn);
    }
    
    int accm = 0, x;
    
    while(m--)
    {
        scanf("%d", &x);
        accm ^= x;
        cout << query(main_root, accm, maxn) << endl;
    }
    
    return 0;
}