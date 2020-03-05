// https://codeforces.com/contest/20/problem/C

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
#define N 100005
#define ll long long
#define MAX 2e18
 
vector<pair<int, ll> >g[N];
int n, m;
 
class prioritize{
public: bool operator()(pair<int, ll> &a, pair<int, ll> &b){
        return a.second > b.second;
    }
};
 
void dijkstra(int a, int b){
    priority_queue<pair<int, ll>, vector<pair<int, ll> >, prioritize> pq;
    pq.push({a, 0});
    
    ll dis[n+1];
    int prev[n+1];
    bool vis[n+1];
    
    for(int i = 0; i <= n; i++){
        prev[i] = -1;
        vis[i] = 0;
    }
    
    dis[a] = 0;
    prev[a] = -1;
    
    for(int i = 1; i <= n; i++)
        if(i != a)
            dis[i] = MAX;
    
    while(!pq.empty()){
        pair<int, ll> tp = pq.top();
        pq.pop();
        
        if(vis[tp.first])
            continue;
        vis[tp.first] = 1;
        
        for(pair<int, ll> i: g[tp.first]){
            if(i.second + tp.second < dis[i.first]){
                dis[i.first] = i.second + tp.second;
                pq.push({i.first, dis[i.first]});
                prev[i.first] = tp.first;
            }
        }
    }
    
    int x = b;
    
    if(prev[x] == -1){
        cout << "-1\n";
        return;
    }
    
    vector<int>print;
    
    while(x != -1){
        print.push_back(x);
        x = prev[x];
    }
    
    for(int i = print.size()-1; i>=0; i--){
        cout << print[i] << " ";
    }
    
    cout << '\n';
}
 
int main(){
    cin >> n >> m;
    int u, v, w;
    
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    
    dijkstra(1, n);
    return 0;
}