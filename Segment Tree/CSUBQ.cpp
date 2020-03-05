// https://www.codechef.com/NOV17/problems/CSUBQ

#include <bits/stdc++.h>
using namespace std;

const int S = 5e5+5;
long long leaf[S], A[S], L, R;

struct node
{
    bool max_present;
    
    long long more;
    long long less;
    
    long long pre_less;
    long long suf_less;
    
    long long last_max;
    long long first_max;
    
    long long size;
    
    node()
    {
        max_present=size=more=less=pre_less=suf_less=last_max=first_max=0ll;
    }
    
} T[4*S];

inline long long range(int l, int r)
{
    return r-l+1;
}

node combine(node a, node b)
{
    node r;
    r.size = a.size + b.size;
    
    r.max_present = a.max_present | b.max_present;
    
    r.pre_less = a.pre_less;
    r.suf_less = b.suf_less;
    
    if(a.pre_less == a.size)
        r.pre_less += b.pre_less;
    if(b.suf_less == b.size)
        r.suf_less += a.suf_less;
    
    if(a.max_present)
        r.first_max = a.first_max;
    else
        r.first_max = a.size + b.first_max;
    
    if(b.max_present)
        r.last_max = a.size + b.last_max;
    else
        r.last_max = a.last_max;
    
    r.less = a.less + b.less + a.suf_less * b.pre_less;
    
    if(!a.max_present && !b.max_present)
    {
        return r;
    }
    
    else if(a.max_present && !b.max_present)
    {
        r.more = a.more + a.last_max * b.size;
    }
    
    else if(!a.max_present && b.max_present)
    {
        r.more = b.more + (b.size - b.first_max + 1) * a.size;
    }

    else
    {
        r.more = a.more + b.more;
        r.more += (a.last_max) * (b.first_max-1);
        r.more += (b.size-b.first_max+1) * (a.size - a.last_max);
        r.more += a.last_max * (b.size - b.first_max + 1);
    }
    
    return r;
}

void build(int n, int l, int r)
{
    if(l==r)
    {
        T[n].size=1;
        leaf[l] = n;
        
        if(A[l] > R)
        {
            T[n].max_present=T[n].more=T[n].first_max=T[n].last_max=1;
        }
        if(A[l] < L)
        {
            T[n].less=T[n].pre_less=T[n].suf_less=1;
        }
        
        return;
    }
    
    int mid=(l+r)/2;
    
    build(n*2,l,mid);
    build(n*2+1,mid+1,r);
    
    T[n]=combine(T[n*2], T[n*2+1]);
}

node query(int n, int l, int r, int ql, int qr)
{
    if(l>r || l>qr || r<ql)
    {
        return node();
    }
    
    if(l>=ql && r<=qr)
    {
        return T[n];
    }
    
    int mid=(l+r)/2;
    return combine(query(n*2, l, mid, ql, qr), query(n*2+1, mid+1, r, ql, qr));
}

void update(int idx, int val)
{
    A[idx]=val;
    
    long long n = leaf[idx];
    T[n]=node();
    T[n].size=1;
    
    if(val > R)
    {
        T[n].max_present=T[n].more=T[n].first_max=T[n].last_max=1;
    }
    if(val < L)
    {
        T[n].less=T[n].pre_less=T[n].suf_less=1;
    }
    
    n/=2;
    
    while(n > 0)
    {
        T[n]=combine(T[n*2], T[n*2+1]);
        n/=2;
    }
}

int main()
{
    int N, Q;
    scanf("%d %d %lld %lld", &N, &Q, &L, &R);
    
    build(1, 1, N);
    
    while(Q--)
    {
        int type;
        scanf("%d", &type);
        
        if(type == 1)
        {
            int x,y;
            scanf("%d %d", &x, &y);
            update(x, y);
        }
        else
        {
            int l, r;
            scanf("%d %d", &l, &r);
            
            long long x = range(l, r);
            long long subarray=(x*(x+1))/2;
            
            node q = query(1, 1, N, l, r);
            if(q.max_present)
                cout << subarray - q.less - q.more << endl;
            else
                cout << subarray - q.less << endl;
        }
    }
    
    return 0;
}