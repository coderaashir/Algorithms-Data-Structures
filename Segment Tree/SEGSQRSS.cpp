// https://www.spoj.com/problems/SEGSQRSS/

#include <bits/stdc++.h>
using namespace std;
 
const int S=1e5+5;
 
long long A[S];
 
struct node
{
    int l;
    int r;
    long long ans;
    long long sum;
    
    node()
    {
        l=r=ans=sum=0;
    }
} T[4*S];
 
inline long long size(node x)
{
    return (x.r-x.l+1);
}
 
struct lazy
{
    bool val;
    bool add_;
    bool set_;
    long long add;
    long long set;
    
    lazy()
    {
        val=add_=set_=add=set=0;
    }
    
} L[4*S];
 
node merge(node a, node b)
{
    node c;
    c.sum=a.sum+b.sum;
    c.ans=a.ans+b.ans;
    c.l=a.l;
    c.r=b.r;
    return c;
}
 
void build(int n, int l, int r)
{
    if(l==r)
    {
        T[n].sum=A[l];
        T[n].ans=A[l]*A[l];
        T[n].l=l;
        T[n].r=r;
        return;
    }
    
    int mid=(l+r)/2;
 
    build(n*2, l, mid);
    build(n*2+1, mid+1, r);
    
    T[n]=merge(T[n*2], T[n*2+1]);
}
 
void push_down(int n, int l, int r)
{
    if(L[n].val)
    {
        if(L[n].set_)
        {
            T[n].sum=size(T[n])*L[n].set;
            T[n].ans=size(T[n])*L[n].set*L[n].set;
            
            if(l!=r)
            {
                L[n*2].val=L[n*2+1].val=true;
                L[n*2].set_=L[n*2+1].set_=true;
                L[n*2].set=L[n*2+1].set=L[n].set;
            }
            
            L[n].set_=false;
        }
        
        if(L[n].add_)
        {
            T[n].ans=T[n].ans + size(T[n])*L[n].add + 2*L[n].add*T[n].sum;
            T[n].sum+=size(T[n])*L[n].add;
            
            if(l!=r)
            {
                L[n*2].val=L[n*2+1].val=true;
                L[n*2].add_=L[n*2+1].add_=true;
                L[n*2].add=L[n*2+1].add=L[n].add;
            }
            
            L[n].add_=false;
        }
        
        L[n].val=false;
    }
 
}
 
void set_value(int n, int l, int r, int ql, int qr, long long val)
{
    push_down(n, l, r);
    
    if(l>qr || r<ql || l>r)
    {
        return;
    }
    
    if(l>=ql && r<=qr)
    {
        T[n].sum=size(T[n])*val;
        T[n].ans=size(T[n])*val*val;
        
        if(l!=r)
        {
            L[n*2].val=L[n*2+1].val=true;
            L[n*2].set=L[n*2+1].set_=val;
            L[n*2].add_=L[n*2+1].add_=false;
            L[n*2].set_=L[n*2+1].set_=true;
        }
        return;
    }
    
    int mid=(l+r)/2;
    set_value(n*2, l, mid, ql, qr, val); set_value(n*2+1, mid+1, r, ql, qr, val);
    T[n]=merge(T[n*2], T[n*2+1]);
}
 
void add_value(int n, int l, int r, int ql, int qr, long long val)
{
    push_down(n, l, r);
    
    if(l>qr || r<ql || l>r)
    {
        return;
    }
    
    if(l>=ql && r<=qr)
    {
        T[n].ans=T[n].ans + size(T[n])*val*val + 2*val*T[n].sum;
        T[n].sum+=size(T[n])*val;
        
        if(l!=r)
        {
            L[n*2].add=L[n*2+1].add=val;
            L[n*2].val=L[n*2+1].val=true;
            L[n*2].add_=L[n*2+1].add_=true;
        }
        
        return;
    }
    
    int mid=(l+r)/2;
    add_value(n*2, l, mid, ql, qr, val); add_value(n*2+1, mid+1, r, ql, qr, val);
    T[n]=merge(T[n*2], T[n*2+1]);
}
 
node query(int n, int l, int r, int ql, int qr)
{
    push_down(n, l, r);
    
    if(l>qr || r<ql || l>r)
    {
        return node();
    }
    
    if(l>=ql && r<=qr)
    {
        return T[n];
    }
    
    int mid=(l+r)/2;
    return merge(query(n*2, l, mid, ql, qr), query(n*2+1, mid+1, r, ql, qr));
}
 
void init()
{
    for(int i=0; i<4*S; i++)
    {
        T[i]=node();
        L[i]=lazy();
        
        if(i<S)
            A[i]=0;
    }
}
 
int main()
{
    int t, N, Q, c=1;
    scanf("%d", &t);
    
    while(t--)
    {
        init();
        scanf("%d %d", &N, &Q);
        
        for(int i=1; i<=N; i++)
            scanf("%lld", &A[i]);
        
        build(1,1,N);
        printf("Case %d:\n", c);
        
        while(Q--)
        {
            int type;
            scanf("%d", &type);
            
            if(type==0)
            {
                int l, r, x;
                scanf("%d %d %d", &l, &r, &x);
                set_value(1, 1, N, l, r, x);
            }
            else if(type==1)
            {
                int l, r, x;
                scanf("%d %d %d", &l, &r, &x);
                add_value(1, 1, N, l, r, x);
            }
            else if(type==2)
            {
                int l, r;
                scanf("%d %d", &l, &r);
                printf("%lld\n", query(1, 1, N, l, r).ans);
            }
        }
        
        c++; 
    }
    
    return 0;
} 