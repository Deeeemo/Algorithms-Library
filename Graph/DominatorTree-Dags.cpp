#include<bits/stdc++.h>

using namespace std;

struct DTreeDag{
	static const int MAXN = 1e6 + 10, LOG = 20;
	int n, sec[MAXN], sz, par[LOG][MAXN], depth[MAXN];
	bool vis[MAXN];
	vector<int> adj[MAXN], res;

	void dfs(int v){
		vis[v] = true;
		for (int u:adj[v])
			if (!vis[u])
				dfs(u);
		sec[sz++] = v;
	}

	int lca(int u, int v){
		if (depth[u] < depth[v]) swap(u, v);
		for (int w = LOG-1; ~w; w--)
			if (depth[u] - (1<<w) >= depth[v])
				u = par[w][u];
		if (u == v) return u;

		for (int w = LOG-1; ~w; w--)
			if (par[w][u] ^ par[w][v])
				u = par[w][u], v = par[w][v];
		return par[0][u];
	}

	vector<int> buildTree(int source) {
		fill(vis, vis + n, 0), sz = 0;
		dfs(source);

		reverse(sec, sec + sz);
		for (int v = 0; v < n; v++) par[0][v] = -1, depth[v] = -1;
		for (int i = 0; i < sz; i++){
			int v = sec[i];
			depth[v] = (~par[0][v]? depth[par[0][v]] + 1: 0);
			
			for (int w = 1; w < LOG; w++)
				if (~par[w-1][v])
					par[w][v] = par[w-1][par[w-1][v]];
				else
					par[w][v] = -1;

			for (int u:adj[v])
				par[0][u] = (par[0][u] == -1? v: lca(par[0][u], v));
		}

		res.assign(par[0], par[0] + n);
		return res;
	}
};

DTreeDag sol;

int main(){
	//Testing the solution
	sol.n = 4;
	sol.adj[0].push_back(1);
	sol.adj[0].push_back(3);
	sol.adj[1].push_back(2);

	vector<int> ans = sol.buildTree(0);
	for (int v = 0; v < 4; v++)
		cout << ans[v] << " ";
	cout << "\n";
	return 0;
}
