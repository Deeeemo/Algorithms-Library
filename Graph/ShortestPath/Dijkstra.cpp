#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define F first
#define S second

const int MAXN = 1e5 + 10;

int n, m, d[MAXN];
vector <pii> adj[MAXN];
set<pii> st;

void update(int v){
	for (auto e:adj[v]){
		int u = e.F, w = e.S;
		if (d[v]+w < d[u]){
			st.erase({d[u], u});
			d[u] = d[v]+w;
			st.insert({d[u], u});
		}
	}
}

void dijk(int v){
	memset(d, 63, sizeof(d));
	d[v] = 0;
	st.insert({d[v], v});
	while (st.size()) {
		int v = st.begin()->S;
		st.erase(st.begin());
		update(v);
	}
}

int main(){

	return 0;
}
