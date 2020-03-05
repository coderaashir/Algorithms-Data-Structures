// https://codeforces.com/contest/706/problem/C

#include <bits/stdc++.h> 
using namespace std;
 
string s[100005][2];
 
int main()
{
    int n;
    scanf("%d", &n);
    
    int c[n+1];
    long long dp[n+1][2];
    
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
    }
    
    for(int i = 1; i <= n; i++)
    {
        cin >> s[i][0];
        s[i][1] = s[i][0];
        reverse(s[i][1].begin(), s[i][1].end());
    }
    
    dp[0][0] = dp[0][1] = 0;
    
    for(int i = 1; i <= n; i++)
    {
        dp[i][0] = dp[i][1] = -1;
        
        if(s[i][0] >= s[i-1][0] && dp[i-1][0] != -1)
        {
            dp[i][0] = dp[i-1][0];
        }
        
        if(s[i][0] >= s[i-1][1])
        {
            if( (dp[i-1][1] < dp[i][0] || dp[i][0] == -1) && dp[i-1][1] != -1)
                dp[i][0] = dp[i-1][1];
        }
        
        if(s[i][1] >= s[i-1][0] && dp[i-1][0] != -1)
        {
            dp[i][1] = dp[i-1][0] + 1LL * c[i];
        }
        
        if(s[i][1] >= s[i-1][1])
        {
            if( (dp[i-1][1] + 1LL * c[i] < dp[i][1] || dp[i][1] == -1) && dp[i-1][1] != -1)
                dp[i][1] = dp[i-1][1] + 1LL * c[i];
        }
    }
    
    long long ans = -1;
    
    if(dp[n][0] != -1)
        ans = dp[n][0];
    
    if(dp[n][1] != -1 && (dp[n][1] < ans || ans == -1))
        ans = dp[n][1];
    
    cout << ans << endl;
    return 0;
}