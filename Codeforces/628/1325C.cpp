#include <iostream>
#include <vector> 
#include <queue> 
#include <map>
using namespace std;

const int N = 1e5+5; 
vector<int>g[N];
int edges[N][2]; 

map<pair<int,int>, int>mp; 

void bfs(int start) {
	bool vis[N]; 
	memset(vis, false, sizeof vis); 
	queue<int>q; 

	q.push(1); 
	vis[1] = true; 

	while(!q.empty()) {
		int tp = q.front();
		q.pop(); 

		for(int k: g[tp]) {
			if(!vis[k]) {
				mp[make_pair(tp, k)] = start; 
				mp[make_pair(k, tp)] = start--; 
				vis[k] = true; 
				q.push(k); 
			}
		}
	}
}

int main() {
	int n; 
	cin >> n; 

	for(int i=1; i<n; i++) {
		cin >> edges[i][0] >> edges[i][1]; 
		g[edges[i][0]].push_back(edges[i][1]); 
		g[edges[i][1]].push_back(edges[i][0]);  
	}

	bfs(n-2);

	for(int i=1; i<n; i++) {
		cout << mp[make_pair(edges[i][0], edges[i][1])] << endl; 
	}
	
	return 0; 
}