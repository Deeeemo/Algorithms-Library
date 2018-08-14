#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 10;
const int MOD = 1e9 + 7;

struct Mat {
	int v[MAXN][MAXN], n, m;
	Mat(int n, int m): n(n), m(m) {
		memset(v, 0, sizeof(v));
	}
	int* operator [](int x) { return v[x]; }
};

Mat mul(Mat a, Mat b){
	Mat ret(a.n, b.m);
	for (int i = 0; i < a.n; i++)
		for (int j = 0; j < b.m; j++)
			for (int w = 0; w < a.m; w++)
				ret[i][j] = (ret[i][j] + 1ll*a[i][w]*b[w][j]) % MOD;
	return ret;
}

Mat pw(Mat a, int b){
	Mat ret(a.n, a.m);
	for (int i = 0; i < ret.n; i++) ret[i][i] = 1;
	while (b){
		if (b & 1)
			ret = mul(ret, a);
		b >>= 1;
		a = mul(a, a);
	}
	return ret;
}

int main(){
	Mat res(2, 1);
	res[0][0] = 1;
	res[1][0] = 0;

	Mat c(2, 2);
	c[0][0] = c[0][1] = c[1][0] = 1;

	int x; cin >> x;
	c = pw(c, x-1);
	res = mul(c, res);
	cout << res[0][0] << endl;
	return 0;
}
