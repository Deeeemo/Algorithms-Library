#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int LOG = 17;

int n, depth[MAXN], par[LOG][MAXN];
vector<int> adj[MAXN];

void plant(int v, int p = -1, int de = 0){
	depth[v] = de;
	par[0][v] = p;
	for (int u:adj[v])
		if (u^p)
			plant(u, v, de+1);
}

void preLCA(){
	for (int w = 1; w < LOG; w++)
		for (int v = 0; v < n; v++)
			if (~par[w-1][v])
				par[w][v] = par[w-1][par[w-1][v]];
			else
				par[w][v] = -1;
}

int lca(int u, int v){
	if (depth[u] < depth[v])
		swap(u, v);
	for (int w = LOG-1; ~w; w--)
		if (depth[u] - (1<<w) >= depth[v])
			u = par[w][u];
	if (u == v) return v;

	for (int w = LOG-1; ~w; w--)
		if (par[w][v] != par[w][u])
			v = par[w][v], u = par[w][u];
	return par[0][v];
}

int main() {
	
	return 0;
}
