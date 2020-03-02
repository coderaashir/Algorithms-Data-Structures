// https://codeforces.com/contest/276/problem/C

#include <bits/stdc++.h> 
using namespace std;
 
const int s=211111;
long long q, N, BIT[s], A[s], pre[s];
 
void update(int index, long long delta)
{
    for(int i=index; i<=N; i+=i&(-i))
    {
        BIT[i]+=delta;
    }
}
 
long long sum(int index)
{
    long long ret=0;
    for(int i=index; i>=1; i-=i&(-i))
    {
        ret+=BIT[i];
    }
    return ret;
}
 
int main()
{
    scanf("%I64d %I64d", &N, &q);
    
    for(int i=1; i<=N; i++)
        scanf("%I64d", &A[i]);
    
    while(q--)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        update(l, 1ll);
        update(r+1, -1ll);
    }
    
    for(int i=1; i<=N; i++)
    {
        pre[i]=sum(i);
    }
    
    sort(A+1, A+N+1);
    sort(pre+1, pre+N+1);
    
    long long ans=0ll;
    for(int i=1; i<=N; i++)
    {
        ans+=pre[i]*A[i];
    }
    cout << ans << endl;
    return 0;
}