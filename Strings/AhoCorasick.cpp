#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;
const int C = 26;

int m, pos[MAXN], nxt[MAXN][C], sz, f[MAXN];
string t[MAXN];

int insert(string &s){
	int cur = 0;
	for (char c:s){
		int x = int(c - 'a');
		if (!nxt[cur][x])
			nxt[cur][x] = ++sz;
		cur = nxt[cur][x];
	}
	return cur;
}

int q[MAXN];
void buildAho(){
	int h = 0, t = 0;
	for (int w = 0; w < C; w++)
		if (nxt[0][w])
			q[t++] = nxt[0][w];

	while (t^h){
		int v = q[h++];
		for (int w = 0; w < C; w++)
			if (nxt[v][w]){
				f[nxt[v][w]] = nxt[f[v]][w];
				q[t++] = nxt[v][w];
			}
			else
				nxt[v][w] = nxt[f[v]][w];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> m;
	for (int i = 0; i < m; i++){
		cin >> t[i];
		pos[i] = insert(t[i]);
	}
	buildAho();
	return 0;
}
