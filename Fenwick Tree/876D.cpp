// https://codeforces.com/contest/876/problem/D

#include <bits/stdc++.h> 
using namespace std;
 
const int s=300005;
int BIT[s];
bool done[s];
 
void update(int x, int delta)
{
    for(int i=x; i<s; i+=i&(-i))
    {
        BIT[i]+=delta;
    }
}
 
int sum(int x)
{
    int ret=0;
    for(int i=x; i>0; i-=i&(-i))
    {
        ret+=BIT[i];
    }
    return ret;
}
 
int main()
{
    int n;
    scanf("%d", &n);
    
    int ans[n+2], last=n+1;
    ans[1]=1;
    
    for(int i=1; i<=n; i++)
    {
        int inp;
        scanf("%d", &inp);
    
        done[inp]=true;
        update(inp, 1);
        
        if(inp==last-1)
        {
            last=inp;
            
            while(done[inp])
            {
                inp--;
            }
            last=inp+1;
        }
        
        ans[i+1]=sum(last-1)+1;
    }
    
    for(int i=1; i<=n+1; i++)
        cout << ans[i] << " ";
    
    cout << endl;
    return 0;
}
