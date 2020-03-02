// https://codeforces.com/contest/380/problem/C

#include <bits/stdc++.h> 
using namespace std;

const int s=1e6+5; 
int A[s], n; 

struct node 
{
    int opening; 
    int closing; 
    int matching; 
    
    node()
    {
        opening=closing=matching=0; 
    }
} T[4*s]; 

node merge(node x, node y)
{
    node ret; 
    int mn=min(x.opening, y.closing); 
    
    ret.opening=x.opening+y.opening-mn; 
    ret.closing=x.closing+y.closing-mn; 
    ret.matching=x.matching+y.matching+2*mn; 

    return ret; 
}

void build(int n, int l, int r)
{
    if(l==r)
    {
        if(A[l])
        {
            T[n].closing=1; 
        }
        else 
        {
            T[n].opening=1; 
        }
        return; 
    }
    
    int mid=(l+r)/2; 
    build(n*2, l, mid); 
    build(n*2+1, mid+1, r); 
    T[n]=merge(T[n*2], T[n*2+1]); 
}

node query(int n, int l, int r, int ql, int qr)
{
    if(l>qr || r<ql || l>r)
    {
        return node(); 
    }
    
    if(l>=ql && r<=qr)
    {
        return T[n]; 
    }
    
    int mid=(l+r)/2; 
    return merge(query(n*2, l, mid, ql, qr), query(n*2+1, mid+1, r, ql, qr)); 
}

int main()
{
    string s; 
    cin >> s; n=s.length();  
    
    for(int i=0; i<s.length(); i++)
    {
        if(s[i]==')')
            A[i+1]=1; 
    }
    
    build(1,1,n); 
    
    int m; 
    scanf("%d", &m); 
    
    while(m--)
    {
        int l, r;
        scanf("%d %d", &l, &r); 
        
        cout << query(1, 1, n, l, r).matching << endl; 
    }
}