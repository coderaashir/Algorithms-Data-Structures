// https://codeforces.com/contest/342/problem/E

#include <bits/stdc++.h> 
using namespace std;

const int INF=1e9+7;
const int LOGN=20;
const int S=100005;

set<int>g[S];
int p[S], level[S], size[S], ans[S], DP[LOGN][S], N, M;

void PreProcessDfs(int node)
{
    if(node != 1)
        level[node]=level[DP[0][node]]+1;
    
    for(int i: g[node]) if(DP[0][node] != i)
    {
        DP[0][i]=node;
        PreProcessDfs(i);
    }
}

void BuildTable()
{
    for(int i=1; i<LOGN; i++)
    {
        for(int j=1; j<=N; j++)
        {
            if(DP[i-1][j]==-1)
                DP[i][j]=-1;
            else
                DP[i][j]=DP[i-1][DP[i-1][j]];
        }
    }
}

int LCA(int a, int b)
{
    if(level[a]>level[b])
        swap(a,b);
    
    int d=level[b]-level[a];
    
    for(int i=LOGN-1; i>=0; i--)
        if((d>>i)&1)
            b=DP[i][b];
    
    if(a==b)
        return a;
    
    for(int i=LOGN-1; i>=0; i--)
    {
        if(DP[i][a] != DP[i][b])
        {
            a=DP[i][a];
            b=DP[i][b];
        }
    }
    
    return DP[0][a];
}

int dist(int u, int v)
{
    return level[u] + level[v] - 2*level[LCA(u,v)];
}

void dfs1(int node, int par)
{
    size[node]=1;
    
    for(int i: g[node]) if(i != par)
    {
        dfs1(i, node);
        size[node]+=size[i];
    }
}

int dfs2(int node, int par, int f)
{
    for(int i: g[node]) if(i != par)
    {
        if(size[i] > f/2)
            return dfs2(i, node, f);
    }
    return node;
}

void decompose(int node, int par)
{
    dfs1(node,-1);
    int centroid=dfs2(node, -1, size[node]);
    
    if(par==-1)
        p[centroid]=centroid;
    else
        p[centroid]=par;
    
    for(auto i=g[centroid].begin(); i!=g[centroid].end(); i++)
    {
        g[*i].erase(centroid);
        decompose(*i, centroid);
    }
    g[centroid].clear();
}

void update(int u)
{
    int x=u;
    while(true)
    {
        ans[x]=min(ans[x], dist(u,x));
        
        if(p[x]==x)
            break;
        x=p[x];
    }
}

int query(int u)
{
    int x=u;
    int ret=INF;
    
    while(true)
    {
        ret=min(ret, dist(u,x)+ans[x]);
        
        if(p[x]==x)
            break;
        
        x=p[x];
    }
    return ret;
}

int main()
{
    scanf("%d %d", &N, &M);
    
    for(int i=1; i<N; i++)
    {
        int u,v;
        scanf("%d %d", &u, &v);
        g[u].insert(v);
        g[v].insert(u);
    }
    
    DP[0][1]=-1;
    PreProcessDfs(1);
    BuildTable();
    decompose(1,-1);
    
    for(int i=1; i<=N; i++)
        ans[i]=INF;
    
    update(1);
    
    for(int i=1; i<=M; i++)
    {
        int t, v;
        scanf("%d %d", &t, &v);
        if(t==1)
        {
            update(v);
        }
        else
        {
            cout << query(v) << endl;
        }
    }
    
    return 0;
}