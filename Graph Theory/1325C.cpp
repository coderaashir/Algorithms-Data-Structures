#include <iostream>
#include <vector> 
#include <queue> 
using namespace std;

const int N = 1e5+5; 
vector<int>g[N];
int edges[N][2]; 

map<pair<int,int>, int>mp; 

void bfs(int start) {
	bool vis[N]; 
	queue<int>q; 

	q.push(1); 
	vis[1] = true; 

	while(!q.empty()) {
		int tp = q.front(); 
		if(vis[tp])
			continue; 

		for(int k: g[tp]) {
			mp[make_pair(tp, k)] = start; 
			mp[make_pair(k, tp)] = start--; 
			q.push(k); 
		}
	}
}

int main() {
	int n; 
	cin >> n; 

	for(int i=1; i<n; i++) {
		cin >> edges[i][0] >> edges[i][1]; 
		g[u].push_back(v); 
		g[v].push_back(u);  
	}

	bfs(n-1); 
	for(int i=1; i<n; i++) {
		cout << mp[make_pair(edges[i][0], edges[i][1])] << endl; 
	}

	return 0; 
}