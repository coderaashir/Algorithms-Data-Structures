// https://codeforces.com/contest/86/problem/D

#include <bits/stdc++.h> 
using namespace std;
 
#define D   1000005
#define MAX 200005
#define BLOCK_SIZE 445
 
int N, t;
int A[MAX];
long long ans[MAX];
int occurences[D];
long long sum;
 
struct Query{
    int left, right;
    int idx;
} queries[MAX];
 
bool comp(Query L, Query R)
{
    if(L.left/BLOCK_SIZE == R.left/BLOCK_SIZE)
    {
        return L.right < R.right;
    }
    else{
        return L.left/BLOCK_SIZE < R.left/BLOCK_SIZE;
    }
}
 
void add(int pos)
{
    sum -= (1LL * occurences[ A[pos] ] * occurences [ A[pos] ] * A[pos]);
    occurences[ A[pos] ]++;
    sum += (1LL * occurences[ A[pos] ] * occurences [ A[pos] ] * A[pos]);
}
 
void remove(int pos)
{
    sum -= (1LL * occurences[ A[pos] ] * occurences [ A[pos] ] * A[pos]);
    
    if(occurences[ A[pos] ] != 0)
        occurences[ A[pos] ]--;
    
    sum += (1LL * occurences[ A[pos] ] * occurences [ A[pos] ] * A[pos]);
}
 
int main(){
 
    scanf("%d %d", &N, &t);
    
    for(int i = 1; i <= N; i++)
    {
        scanf("%d", &A[i]);
    }
    
    for(int i = 1; i <= t; i++)
    {
        scanf("%d %d", &queries[i].left, &queries[i].right);
        queries[i].idx = i;
    }
    
    sort(queries+1, queries+1+t, comp);
 
    int cur_L = 1, cur_R = 1;
    
    for(int i = 1; i <= t; i++)
    {
        
        while(cur_R <= queries[i].right)
        {
            add(cur_R);
            cur_R++;
        }
        
        while(cur_L > queries[i].left)
        {
            add(cur_L-1);
            cur_L--;
        }
        
        while(cur_L < queries[i].left)
        {
            remove(cur_L);
            cur_L++;
        }
        
        while(cur_R > queries[i].right+1)
        {
            remove(cur_R-1);
            cur_R--;
        }
        
        ans[ queries[i].idx ] = sum;
    }
    
    for(int i = 1; i <= t; i++)
    {
        cout << ans[i] << endl;
    }
    
    return 0;
}