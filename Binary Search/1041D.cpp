// https://codeforces.com/contest/1041/problem/D

#include <bits/stdc++.h> 
using namespace std;

int n, h;
long long x[200005][2];
const long long MAX = 1e9;

long long max(long long a, long long b)
{
    return (a>b)? a:b;
}

long long binary(long long start, long long sum, long long x1, long long x2)
{
    long long low = x1, high = x2;
    long long ans = low - start;
    
    while(low <= high)
    {
        long long mid = (low+high)/2;
        if((mid - start) - sum <= h)
        {
            ans = mid;
            low = mid+1;
        }
        else
        {
            high = mid-1;
        }
    }
    
    return ans-start;
}

int main()
{
    long long ans = -1;
    cin >> n >> h;
    
    for(int i=1; i<=n; i++)
        cin >> x[i][0] >> x[i][1];
    
    int lt=1, rt=1;
    long long sum = x[1][1] - x[1][0];
    
    for(int i=2; i<=n; i++)
    {
        if( (x[i][1] - x[1][0]) - (sum + (x[i][1] - x[i][0])) < h)
        {
            rt = i;
            sum += (x[i][1] - x[i][0]);
        }
        else
            break;
    }
    
    if(rt == n)
    {
        cout << (h+sum) << endl;
        return 0;
    }
    
    ans = max(ans, binary(x[1][0], sum, x[rt][1], x[rt+1][0]));
    // cout << ans << endl;
    
    while(lt <= n && rt <= n)
    {
        sum -= (x[lt][1] - x[lt][0]);
        ++lt;
        
        for(int i=rt+1; i<=n; i++)
        {
            if( (x[i][1] - x[lt][0]) - (sum + (x[i][1] - x[i][0])) < h)
            {
                rt = i;
                sum += (x[i][1] - x[i][0]);
            }
            else
                break;
        }
        if(rt == n)
        {
            ans = max(ans, h+sum);
            break;
        }
        ans = max(ans, binary(x[lt][0], sum, x[rt][1], x[rt+1][0]));
    }
    
    cout << ans << endl;
    return 0;
}