//reads t s
//outputs number of times t appears in s
//https://www.spoj.com/problems/NAJPF/
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;

string t, s;
int m, n, f[MAXN], k;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t >> s;
	m = t.size(), n = s.size();

	k = 0;
	for (int i = 2; i <= m; i++){
		while (k && t[i-1] != t[k]) k = f[k];
		if (t[i-1] == t[k]) k++;
		f[i] = k;
	}

	k = 0;
	int ans = 0;
	for (int i = 0; i < n; i++){
		while (k && s[i] != t[k]) k = f[k];
		if (s[i] == t[k]) k++;
		if (k == m){
			k = f[k];
			ans++;
		}
	}
	cout << ans << "\n";
	return 0;
}
