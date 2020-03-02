// https://codeforces.com/contest/384/problem/E

#include <bits/stdc++.h> 
using namespace std;

const int sz = 200005;

int A[sz], start[sz], finish[sz], p[sz], timer, N, M;
vector<int>g[sz];

struct Fenwick
{
    int BIT[sz];
    
    void update(int idx, int delta)
    {
        for(int i=idx; i<=N; i+=i&(-i))
        {
            BIT[i]+=delta;
        }
    }
    
    int sum(int idx)
    {
        int ret=0;
        for(int i=idx; i>=1; i-=i&(-i))
        {
            ret+=BIT[i];
        }
        return ret;
    }

} odd, even;

void dfs(int node, int parent)
{
    if(node!=1)
        p[node]=p[parent]^1;
    
    start[node]=++timer;
    
    for(int i: g[node]) if(i!=parent)
    {
        dfs(i,node);
    }
    
    finish[node]=timer;
}



int main()
{
    scanf("%d %d", &N, &M);
    
    for(int i=1; i<=N; i++)
    {
        scanf("%d", &A[i]);
    }
    
    for(int i=1; i<N; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    dfs(1,-1);
    
    for(int i=1; i<=M; i++)
    {
        int type;
        scanf("%d", &type);
        
        if(type==1)
        {
            int x, val;
            scanf("%d %d", &x, &val);
            
            if(p[x]%2)
            {
                odd.update(start[x], val);
                odd.update(finish[x]+1, -val);
                even.update(start[x], -val);
                even.update(finish[x]+1, val);
            }
            else
            {
                odd.update(start[x],-val);
                odd.update(finish[x]+1, val);
                even.update(start[x], val);
                even.update(finish[x]+1, -val);
            }
        }
        else
        {
            int x;
            scanf("%d", &x);
            if(p[x]%2)
            {
                cout << A[x]+odd.sum(start[x]);
            }
            else
            {
                cout << A[x]+even.sum(start[x]);
            }
            cout << endl;
        }
    }
    
    return 0;
}