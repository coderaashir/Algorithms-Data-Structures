// https://codeforces.com/contest/165/problem/E

#include <bits/stdc++.h> 
using namespace std;

const int sz = 1e6+5;
int N, A[sz], P[4194309];
int dp[4194304];

int main()
{
    memset(P, 0, sizeof P);
    memset(dp, -1, sizeof dp);

    scanf("%d", &N);
    
    for(int i = 1; i <= N; i++)
    {
        scanf("%d", &A[i]);
        P[A[i]] = 1;
    }
    
    for(int mask = 0; mask <= (1<<22)-1; mask++)
    {
        if(P[mask])
            dp[mask] = mask;
        
        if(mask & 1 && P[mask^1])
            dp[mask] = mask^1;
    }
    
    for(int p = 0; p <= 22; p++) for(int mask = 0; mask <= (1<<22)-1; ++mask)
    {
        if(mask & (1 << p) && dp[mask^(1<<p)] != -1)
            dp[mask] = dp[mask^(1<<p)];
    }
    
    for(int i = 1; i <= N; i++)
    {
        int k = (1 << 22) - 1 - A[i];
        cout << dp[k] << " ";
    }
        
    cout << endl;
    return 0;
}