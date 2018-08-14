/*
   Memory-Efficient sieve of Eratosthenes, also known as the segmented sieve.

   Resources:
   https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Segmented_sieve

   Problems for Practice:
   http://codeforces.com/contest/1017/problem/F
*/

#include<bits/stdc++.h>

using namespace std;

const int MAXN = 3e8;
const int SQ = 18e3;

int primes[SQ], sz;
bool mark[SQ + 2];

int main() {
	mark[1] = true;
	for (int i = 2; i <= SQ; i++)
		if (!mark[i]) {
			for (int j = i; j <= SQ; j += i)
				mark[j] = true;
			primes[sz++] = i;
		}

	for (int l = SQ+1; l < MAXN; l += SQ){
		memset(mark, 0, sizeof(mark));
		int r = min(MAXN, l + SQ);
		for (int i = 0; i < sz; i++){
			int tl = (l + (primes[i]-1))/ primes[i] * primes[i];
			while (tl < r){
				mark[tl - l] = true;
				tl += primes[i];
			}
		}
	}
	return 0;
}
