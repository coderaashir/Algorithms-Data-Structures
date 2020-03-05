// https://www.codechef.com/APRIL17/problems/SMARKET
#include <bits/stdc++.h> 
using namespace std;

int readint()
{
    int cc = getc(stdin);
    for (;cc < '0' || cc > '9';)  cc = getc(stdin);
    int ret = 0;
    for (;cc >= '0' && cc <= '9';)
    {
        ret = ret * 10 + cc - '0';
        cc = getc(stdin);
    }
    return ret;
}

#define N 111111
#define A 1111111
#define Q 211111
#define BLOCK 555

struct node{
    int L, R, K, idx;
};

int b[N];
int a[N];
int distinct[A]; // numbers of times item i has got repeated
node q[N];
int ans[N];
int k_times[A];

int n, m;
int total = 0;

bool cmp(node x, node y){
    if(x.L/BLOCK == y.L/BLOCK){
        return x.R < y.R;
    }
    
    return x.L/BLOCK < y.L/BLOCK;
}

void add(int pos){
    distinct[ a[pos] ]++;
    k_times [ distinct[ a[pos] ] ]++;
}

void remove(int pos){
    k_times [ distinct[ a[pos] ] ]--;
    distinct[ a[pos] ]--;
}

int main(){
    int T;
    scanf("%d", &T);
    
    while(T--){
        n = readint();
        m = readint();
    
        for(int i = 0; i < n; i++)
            b[i] = readint();
        
        a[0] = 1;
        int cnt = 1;
    
        for(int i = 1; i < n; i++){
            if( b[i-1] == b[i] ){
                a[i] = a[i-1];
            }
            else{
                cnt++;
                a[i] = cnt;
            }
        }
    
    
        for(int i = 0; i < m; i++){
            q[i].L = readint();
            q[i].R = readint();
            q[i].K = readint();
        
            q[ i ].L--, q[ i ].R--;
            q[i].idx = i;
        }
    
        sort(q, q+m, cmp);
    
        int currentL = 0, currentR = 0;
    
        for(int i = 0; i < m; i++){
        
            while(currentR <= q[i].R){
                add(currentR);
                currentR++;
            }
        
            while(currentL > q[i].L){
                add(currentL-1);
                currentL--;
            }
        
            while(currentL < q[i].L){
                remove(currentL);
                currentL++;
            }
        
            while(currentR > q[i].R+1){
                remove(currentR-1);
                currentR--;
            }
        
            ans[ q[ i ].idx ] = k_times[ q[i].K ];
        }
    
        for(int i = 0; i < m; i++){
            printf("%d\n", ans[i]);
        }
        
        memset(k_times, 0, sizeof k_times);
        memset(distinct, 0, sizeof distinct);
    }
    
    return 0;
}