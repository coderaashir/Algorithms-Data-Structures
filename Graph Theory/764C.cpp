// https://codeforces.com/contest/764/problem/C

#include <bits/stdc++.h> 
using namespace std;
 
#define N 1111111
vector<int>adj[N];
int color[N];
int n;
bool vis[N];
 
bool dfs(int u, int c){
    
    vis[u] = 1;
    bool can, flag = 1;
    
    for(int i: adj[u]){
        
        can = 0;
        
        if(vis[i])
            continue;
        
        if(color[i] != c){
            // cout << i << endl;
            return 0;
        }
        
        else{
            can = dfs(i, c);
            
            if(!can){
                flag = 0;
                break;
            }
        }
    }
    
    return flag;
}
 
int main(){
    
    scanf("%d", &n);
    
    for(int i = 1; i < n; i++){
        int u,v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    for(int i = 1; i <= n; i++)
        scanf("%d", &color[i]);
    
    int e1 = -1;
    int e2 = -1;
    
    for(int i = 1; i <= n; i++){
        
        if( color[adj[i][0]] != color[i] ){
            e1 = i;
            e2 = adj[i][0];
            // cout << adj[i][0] << " " << i << endl;
        }
        
    }
    
    if(e1 == -1 && e2 == -1){
        printf("YES\n1\n");
        return 0;
    }
    
    else{
        
        bool can = 0;
        bool flag = 1;
        vis[e1] = 1;
        
        for(int i: adj[e1]){
            
            can = dfs(i, color[i]);
            
            if(!can){
                flag = 0;
                break;
            }
        }
        
        if(flag){
            printf("YES\n%d\n", e1);
            return 0;
        }
        
        memset(vis, 0, sizeof vis);
        can = 0;
        
        vis[e2] = 1;
        
        for(int i: adj[e2]){
            can = dfs(i, color[i]);
            
            if(!can){
                flag = 0;
                break;
            }
        }
        
        if(can){
            printf("YES\n%d\n", e2);
            return 0;
        }
        
    }
    
    printf("NO\n");
    return 0;
}