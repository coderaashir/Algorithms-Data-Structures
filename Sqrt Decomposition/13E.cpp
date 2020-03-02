// https://codeforces.com/contest/13/problem/E

#include <bits/stdc++.h> 
using namespace std;

const int n=1e5+5;
const int sqrt_n=350;

int N, M, A[n];
int number_of_jumps[n], last[n];

void update(int hole, int value)
{
    A[hole]=value;
    
    for(int j=hole; j/sqrt_n == hole/sqrt_n && j>0; j--)
    {
        if((j+A[j])/sqrt_n == hole/sqrt_n && j+A[j]<=N)
        {
            last[j]=last[j+A[j]];
            number_of_jumps[j]=1+number_of_jumps[j+A[j]];
        }
        else
        {
            last[j]=j;
            number_of_jumps[j]=1;
        }
    }
}

int main()
{
    scanf("%d %d", &N, &M);
    
    for(int i=1; i<=N; i++)
    {
        scanf("%d", &A[i]);
    }
    
    for(int i=N; i>=1; i--)
    {
        if((i+A[i])/sqrt_n == i/sqrt_n && i+A[i]<=N)
        {
            last[i]=last[i+A[i]];
            number_of_jumps[i]=1+number_of_jumps[i+A[i]];
        }
        else
        {
            last[i]=i;
            number_of_jumps[i]=1;
        }
    }
    
    for(int i=1; i<=M; i++)
    {
        int type;
        scanf("%d", &type);
        
        if(type==0)
        {
            int a,b;
            scanf("%d %d", &a, &b);
            update(a,b);
        }
        else
        {
            int a;
            scanf("%d", &a);
            
            int las=0,count=0;
            
            for(; a<=N; las=last[a], a=las+A[las])
            {
                count += number_of_jumps[a];
            }
            printf("%d %d\n", las, count);
        }
    }
    return 0;
}
