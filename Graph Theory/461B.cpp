// https://codeforces.com/contest/461/problem/B

#include <bits/stdc++.h> 
using namespace std;
 
const int N = 1e5+5;
const int MOD = 1e9+7;
 
int color[N];
long long DP[N][2];
vector<int>g[N];
 
void dfs(int cur, int par)
{
    DP[cur][1] = 0;
    DP[cur][0] = 1;
    
    for(int v: g[cur])
    {
        if(v == par)
            continue;
        
        long long old[2];
        old[0] = DP[cur][0];
        old[1] = DP[cur][1];
        
        DP[cur][0] = DP[cur][1] = 0;
    
        dfs(v, cur);
        
        DP[cur][0] += old[0] * DP[v][0];
        DP[cur][0] %= MOD;
        DP[cur][1] += old[0] * DP[v][1];
        DP[cur][1] %= MOD;
        DP[cur][1] += old[1] * DP[v][0];
        DP[cur][1] %= MOD;
        
        DP[cur][1] += old[1] * DP[v][1];
        DP[cur][1] %= MOD;
        DP[cur][0] += old[0] * DP[v][1];
        DP[cur][0] %= MOD;
    }
    
    if(color[cur] == 1)
    {
        DP[cur][1] = DP[cur][0];
        DP[cur][0] = 0;
    }
}
 
int main()
{
    int n;
    scanf("%d", &n);
    
    for(int i = 2; i <= n; i++)
    {
        int p;
        scanf("%d", &p);
        
        g[p+1].push_back(i);
        g[i].push_back(p+1);
    }
    
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &color[i]);
    }
    
    dfs(1, 0);
    cout << DP[1][1] << endl;
    
    return 0;
}