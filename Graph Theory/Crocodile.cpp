// https://wcipeg.com/problem/ioi1121

#include<bits/stdc++.h> 
using namespace std;

const int s=111111;
const int inf=INT_MAX;

bool vis[s], p[s];
int N, M, K, dis1[s], dis2[s];
vector<pair<int,int> >g[s];

class cmp
{
public: bool operator()(pair<int, int>a, pair<int, int>b)
    {
        return a.second>b.second;
    }
};

priority_queue<pair<int, int>, vector<pair<int, int> >, cmp>pq;

void dijkstra()
{
    while(!pq.empty())
    {
        pair<int,int>tp=pq.top();
        pq.pop();
        
        if(vis[tp.first])
            continue;
        
        vis[tp.first]=true;
        int a=tp.first;
        
        for(pair<int,int> i: g[a])
        {
            int c=i.first, d=i.second;
            
            if(dis1[c]>d+dis2[a])
            {
                dis2[c]=dis1[c];
                dis1[c]=d+dis2[a];
                pq.push({c,dis2[c]});
            }
            else if(dis2[c]>d+dis2[a])
            {
                dis2[c]=d+dis2[a];
                pq.push({c,dis2[c]});
            }
        }
    }
}

int main()
{
    scanf("%d %d %d", &N, &M, &K);
    
    for(int i=1; i<=N; i++)
    {
        dis1[i]=dis2[i]=inf;
    }
    
    for(int i=1; i<=M; i++)
    {
        int u,v,w;
        scanf("%d %d %d", &u,&v,&w);
        u++; v++;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    
    for(int i=1; i<=K; i++)
    {
        int P;
        scanf("%d", &P);
        P++;
        p[P]=true;
        pq.push({P,0});
        dis1[P]=dis2[P]=0;
    }
    
    dijkstra();
    cout << dis2[1] << endl;
    return 0;
}