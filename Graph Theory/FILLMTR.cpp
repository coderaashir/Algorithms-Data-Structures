// https://www.codechef.com/SEPT17/problems/FILLMTR

#include <bits/stdc++.h> 
using namespace std;

const int sz = 1e5+5;
vector<int>nodes;
vector<pair<int, int> >g[sz];
int N, Q, A[sz];
bool vis[sz];

void init()
{
    for(int i = 0; i <= N; i++)
    {
        g[i].clear();
        vis[i] = false;
        A[i] = 0;
    }
    nodes.clear();
}

bool bfs(int start)
{
    queue<int>q;
    q.push(start);
    vis[start] = true;
    
    while(!q.empty())
    {
        int tp = q.front();
        q.pop();
        
        for(pair<int,int> i: g[tp])
        {
            int a = i.first, b = i.second;
            
            if(vis[a])
            {
                if(b == 0 && A[a] != A[tp])
                    return false;
                if(b == 1 && A[a] == A[tp])
                    return false;
                continue;
            }
            
            if(b == 1)
                A[a] = !A[tp];
            else
                A[a] = A[tp];
            
            q.push(a);
            vis[a] = true;
        }
    }
    
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);
    
    while(T--)
    {
        bool pos = true;
        scanf("%d %d", &N, &Q);
        init();
        
        while(Q--)
        {
            int u, v, k;
            scanf("%d %d %d", &u, &v, &k);
            
            if(u == v && k != 0)
            {
                pos = false;
                cout << "no\n";
            }
            
            g[u].push_back({v,k});
            g[v].push_back({u,k});
            nodes.push_back(u);
            nodes.push_back(v);
        }
        
        if(!pos)
            continue;
        
        for(int i: nodes)
        {
            if(!vis[i])
            {
                pos = pos & bfs(i);
            }
            if(!pos)
                break;
        }
        
        if(pos)
            cout << "yes\n";
        else
            cout << "no\n";
    }
}