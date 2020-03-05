// https://www.codechef.com/problems/ALTSUB

#include <bits/stdc++.h> 
using namespace std;

const int MOD = 1e9+7;
const int sz = 1e5+5;
long long A[sz];
int N, M;

int mod(long long x)
{
    return x % MOD;
}

struct node
{
    long long oddc, evenc;
    long long odds, evens;
    long long odd_ss, even_ss;
    
    node()
    {
        oddc = evenc = odds = evens = odd_ss = even_ss = 0;
    }
    
} T[4*sz];
int L[sz];

node merge(node a, node b)
{
    node tmp;
    tmp.oddc = mod((a.oddc*b.evenc)%MOD + (a.evenc*b.oddc)%MOD + a.oddc + b.oddc);
    tmp.evenc = mod((a.oddc*b.oddc)%MOD + (a.evenc*b.evenc)%MOD + a.evenc + b.evenc);
    tmp.odds = mod(a.odds + b.odds + (a.odds*b.evenc)%MOD+MOD - (b.evens*a.oddc)%MOD + (a.evens*b.oddc)%MOD + (b.odds*a.evenc)%MOD);
    tmp.evens = mod((a.odds*b.oddc)%MOD+MOD - (b.odds*a.oddc)%MOD + (a.evens*b.evenc)%MOD + (b.evens*a.evenc)%MOD + (a.evens+b.evens)%MOD);
    tmp.odd_ss = mod((a.odd_ss*b.evenc)%MOD + (b.even_ss*a.oddc)%MOD+MOD - (2LL * a.odds * b.evens)%MOD);
    tmp.odd_ss += mod((a.odd_ss+b.odd_ss)%MOD + (a.even_ss*b.oddc)%MOD + (b.odd_ss*a.evenc)%MOD + (2LL*a.evens*b.odds)%MOD);
    tmp.even_ss = mod((a.odd_ss*b.oddc)%MOD + (b.odd_ss*a.oddc)%MOD + (a.even_ss*b.evenc)%MOD + (b.even_ss*a.evenc)%MOD);
    tmp.even_ss += mod((a.even_ss+b.even_ss)%MOD+MOD - (2LL*a.odds*b.odds)%MOD + (2LL*a.evens*b.evens)%MOD);
    return tmp;
}

void build(int first, int last, int Node)
{
    if(first == last)
    {
        T[Node].oddc = 1; T[Node].evenc = 0;
        T[Node].odds = A[first]; T[Node].evens = 0;
        T[Node].odd_ss = (A[first] * A[first]) % MOD; T[Node].even_ss = 0;
        L[first] = Node;
        return;
    }
    
    int mid = (first + last)/2;
    build(first, mid, Node*2);
    build(mid+1, last, Node*2+1);
    T[Node] = merge(T[Node*2], T[Node*2+1]);
}

void update(int index, long long val)
{
    int Node = L[index];
    T[Node].oddc = 1; T[Node].evenc = 0;
    T[Node].odds = val; T[Node].evens = 0;
    T[Node].odd_ss = (val*val)%MOD; T[Node].even_ss = 0;
    
    Node /= 2;
    
    while(Node > 0)
    {
        T[Node] = merge(T[Node*2], T[Node*2+1]);
        Node/=2;
    }
}

node query(int first, int last, int q_first, int q_last, int node)
{
    struct node ret;
    
    if(first > last)
        return ret;
    
    if(first > q_last || last < q_first)
        return ret;
    
    if(first >= q_first && last <= q_last)
        return T[node];
    
    int mid = (first + last)/2;
    struct node a = query(first, mid, q_first, q_last, node*2);
    struct node b = query(mid+1, last, q_first, q_last, node*2+1);
    ret = merge(a, b);
    return ret;
}

int main()
{
    
    int N, M;
    scanf("%d %d", &N, &M);
    
    for(int i = 1; i <= N; i++)
        scanf("%lld", &A[i]);
    
    build(1, N, 1);
    
    while(M--)
    {
        int type, i, j;
        scanf("%d %d %d", &type, &i, &j);
        
        if(type == 1)
        {
            A[i] = j;
            update(i, j);
        }
        
        else
        {
            struct node ans = query(1, N, i, j, 1);
            cout << (ans.odd_ss+ans.even_ss)%MOD << endl;
        }
    }
    
    return 0;
}