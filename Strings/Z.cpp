//finds the Z array of a string
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;

string s;
int n, z[MAXN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> s;
	n = s.size();
	int l = 0, r = 0;
	for (int i = 1; i < n; i++)
		if (r <= i){
			l = r = i;
			while (r < n && s[r] == s[r-l]) r++;
			z[i] = r-i;
		}
		else{
			if (z[i-l] < (r - i))
				z[i] = z[i-l];
			else{
				l = i;
				while (r < n && s[r] == s[r-l]) r++;
				z[i] = r-i;
			}
		}

	for (int i = 0; i < n; i++)
		cout << z[i] << " ";
	cout << "\n";
	return 0;
}
