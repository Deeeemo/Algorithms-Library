/*
	Lexicographically minimal string rotation
	
	Resources:
	https://en.m.wikipedia.org/wiki/Lexicographically_minimal_string_rotation
*/
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;

int f[MAXN];
int findIndex(string s){
	s += s; //XXX be careful of MAXN
	int ind = 0, k = 0;
	memset(f, 0, sizeof(f));

	for (int i = 1; i < (int)s.size(); i++){
		while (k && s[i] != s[ind + k]) {
			if (s[i] < s[ind + k])
				ind = i - k;
			k = f[k];
		}
		
		if (s[i] != s[ind + k]){
			if (s[i] < s[ind + k])
				ind = i;
			f[i - ind + 1] = 0;
		}
		else
			f[i - ind + 1] = ++k;
	}

	return ind;
}

int main(){
	string s;
	cin >> s;
	cout << findIndex(s) << "\n";
	return 0;
}
