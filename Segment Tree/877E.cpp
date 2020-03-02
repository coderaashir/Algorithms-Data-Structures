// https://codeforces.com/contest/877/problem/E

#include <bits/stdc++.h> 
using namespace std;

const int s=200005;
vector<int>g[s];
bool L[8*s];
int A[s], P[s], start[s], finish[s], inverse[s], timer=0;

void dfs(int node)
{
    start[node]=++timer;
    inverse[start[node]]=node;
    
    for(int i: g[node])
    {
        dfs(i);
    }
    
    finish[node]=timer;
}

struct node
{
    int on;
    int off;
    node()
    {
        on=off=0;
    }
} T[8*s];

void build(int n, int first, int last)
{
    if(first==last)
    {
        if(A[inverse[first]]==1)
            T[n].on=1;
        else
            T[n].off=1;
        return;
    }
    int mid=(first+last)/2;
    build(n*2,first,mid);
    build(n*2+1,mid+1,last);
    
    T[n].on=T[n*2].on+T[n*2+1].on;
    T[n].off=T[n*2].off+T[n*2+1].off;
}

int query(int n, int l, int r, int ql, int qr)
{
    if(l>r || l>qr || r<ql)
    {
        return 0;
    }
    if(L[n])
    {
        swap(T[n].on, T[n].off);
        L[n]=false;
        
        if(l!=r)
        {
            L[n*2]=!L[n*2];
            L[n*2+1]=!L[n*2+1];
        }
    }
    if(l>=ql && r<=qr)
    {
        return T[n].on;
    }
    
    int mid=(l+r)/2;
    return query(n*2, l, mid, ql, qr) + query(n*2+1, mid+1, r, ql, qr);
}

void update(int n, int l, int r, int ql, int qr)
{
    if(L[n])
    {
        swap(T[n].on, T[n].off);
        L[n]=false;
        if(l!=r)
        {
            L[n*2]=!L[n*2];
            L[n*2+1]=!L[n*2+1];
        }
    }
    if(l>r || l>qr || r<ql)
    {
        return;
    }
    if(l>=ql && r <= qr)
    {
        swap(T[n].on, T[n].off);
        
        if(l!=r)
        {
            L[n*2]=!L[n*2];
            L[n*2+1]=!L[n*2+1];
        }
        return;
    }
    int mid=(l+r)/2;
    
    update(n*2, l, mid, ql, qr);
    update(n*2+1, mid+1, r, ql, qr);
    
    T[n].on = T[n*2].on + T[n*2+1].on;
    T[n].off = T[n*2].off + T[n*2+1].off;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    for(int i=2; i<=n; i++)
    {
        scanf("%d", &P[i]);
        g[P[i]].push_back(i);
    }
    
    dfs(1);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &A[i]);
    }
    
    build(1,start[1],finish[1]);
    
    int q;
    scanf("%d", &q);
    
    while(q--)
    {
        string s;
        cin >> s;
        
        if(s=="get")
        {
            int x;
            scanf("%d", &x);
            cout << query(1, start[1], finish[1], start[x], finish[x]) << endl;
        }
        else
        {
            int x;
            scanf("%d", &x);
            update(1, start[1], finish[1], start[x], finish[x]);
        }
    }
}