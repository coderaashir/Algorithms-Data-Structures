// https://wcipeg.com/problem/coci073p6

#include <bits/stdc++.h> 
#include <iostream>
using namespace std;

const int sz = 250005;
int N, M;
int A[10], Ar[sz];

struct data {
    int A[10];
    int sum;
} T[3*sz];

int Lazy[3*sz];

int mod(int x)
{
    while(x < 0)
        x += 10;
    x %= 10;
    return x;
}

void combine(int node)
{
    for(int i = 0; i <= 9; i++)
    {
        T[node].A[i] = T[node*2].A[i] + T[node*2+1].A[i];
    }
    T[node].sum = T[node*2].sum + T[node*2+1].sum;
}

void change(int node, int val)
{
    T[node].sum = 0;
    
    for(int i=0; i<10; i++)
        A[i] = T[node].A[i];
    
    for(int i=0; i<=9; i++)
    {
        T[node].A[i] = A[mod(i-val)];
        T[node].sum += i*T[node].A[i];
    }
}

void push_down(int node, int l, int r)
{
    change(node*2, Lazy[node]);
    change(node*2+1, Lazy[node]);
    
    Lazy[2*node] += Lazy[node];
    Lazy[2*node+1] += Lazy[node];
    
    Lazy[2*node] = mod(Lazy[2*node]);
    Lazy[2*node+1] = mod(Lazy[2*node+1]);
}

int query(int node, int ql, int qr, int l, int r)
{
    if(Lazy[node] != 0)
    {
        if(l != r)
            push_down(node, l, r);
        Lazy[node] = 0;
    }
    
    if(l > qr || r < ql || l > r)
        return 0;
    
    if(l >= ql && r <= qr)
    {
        int ret = T[node].sum;
        change(node, 1);
        Lazy[node]++;
        Lazy[node] = mod(Lazy[node]); 
        return ret;
    }
    else
    {
        int mid = (l+r)/2;
        int sum = query(node*2, ql, qr, l, mid) + query(node*2+1, ql, qr, mid+1, r);
        combine(node);
        return sum;
    }
}

void build(int node, int l, int r)
{
    if(l == r)
    {
        T[node].A[Ar[l]] = 1;
        T[node].sum = Ar[l];
    }
    else
    {
        int mid = (l+r)/2;
        build(node*2, l, mid);
        build(node*2+1, mid+1, r);
        combine(node);
    }
}

int main()
{
    scanf("%d%d", &N, &M);
    string s;
    cin >> s;
    
    for(int i=0; i<s.length(); i++)
    {
        Ar[i+1] = s[i]-'0';
    }
    
    build(1, 1, N);
    
    for(int i=1; i<=M; i++)
    {
        int A, B;
        scanf("%d%d", &A, &B);
        cout << query(1, A, B, 1, N) << endl;
    }
    
    return 0;
}
