#include <iostream>
#include <vector> 
using namespace std; 

const int N = 2e5+5; 
vector<int>g[N]; 
int par[N], end[N], in[N], out[N], depth[N]; 
bool vis[N]; 

int cur_t = 0; 

void dfs(int root) {
	in[root] = cur_t++;
	vis[root] = true; 

	for(int i: g[root]) {
		if(!vis[i]) {
			par[i] = root; 
			depth[i] = depth[root]+1; 
			dfs(i); 
		}
	}

	out[root] = cur_t++; 
}

int main() {
	int n, m;
	cin >> n >> m;

	for(int i=1; i < n; i++) {
		int u, v; 
		cin >> u >> v; 
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vector<pair<int,int> > v;
	
	dfs(1);
	par[1] = 1;
 
	for(int i=1; i<=m; i++) {
		int inp, k; 
		cin >> k; 


		for(int j=1; j<=k; j++) {
			cin >> inp; 
			v.push_back(make_pair(depth[inp], par[inp])); 
		}

		sort(v.begin(), v.end()); 
		bool done = false; 

		for(int i=1; i < k; i++) {
			int node = v[i].second;
			int prev = v[i-1].second; 

			if(in[node] >= in[prev] && out[node] <= out[prev])
				continue; 
			done = true; 
			cout << "NO" << endl; 
			break; 
		}

		if(!done) {
			cout << "YES" << endl; 
		}

		v.clear(); 
	}
	return 0; 
}