#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define F first
#define S second

const int MAXN = 1e5 + 10;

int n, m;
vector<pii> adj[MAXN];

bool mark[MAXN];
int q[MAXN], par[MAXN];
ll d[MAXN];

void spfa(int v){
	memset(d, 63, sizeof(d));
	memset(mark, 0, sizeof(mark));
	memset(par, -1, sizeof(par));
	int h = 0, t = 0;
	d[v] = 0;
	q[t++] = v;
	mark[v] = true;
	while (t^h){
		v = q[h++];
		if (h == MAXN) h = 0;
		mark[v] = false;
		for (auto e:adj[v]){
			int u = e.F, w = e.S;
			if (d[v] + w < d[u]){
				d[u] = d[v] + w;
				par[u] = v;
				if (!mark[u]){
					q[t++] = u;
					if (t == MAXN) t = 0;
					mark[u] = true;
				}
			}
		}
	}
}

int main(){
	
	return 0;
}
