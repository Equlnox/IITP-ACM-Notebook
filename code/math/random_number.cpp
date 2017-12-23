#include <bits/stdc++.h>

using namespace std;

using LL = long long;
template<typename T> using V = vector<T>; 
template<typename T, typename S> using P = pair<T, S>; 
template<class T> using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;
using LD = long double;

#define ALL(v) v.begin(), v.end()
#define endl '\n'
#define SYNC ios_base::sync_with_stdio(false); cin.tie(NULL); cerr.tie(NULL);
#define REP(i, n) for(int i = 0; i < (int)n ;i++)
#define REPN(i, n) for(int i = 1; i <= (int)n ; i++)
#define her 	cerr << "here\n" 
#define pp push_back
#define fi first 
#define se second
#define un(x) x.erase(unique(ALL(x)), x.end())

template<typename T, typename S> void check(T & a, S & b) { if (a >= b) { a %= b; } }
template<typename T>T gcd(T u, T v) { if (u == v)return u; if (u == 0)return v; if (v == 0)return u; if (~u & 1) { if (v & 1) return gcd(u >> 1, v); else return gcd(u >> 1, v >> 1) << 1; }if (~v & 1)return gcd(u, v >> 1); if (u > v)return gcd((u - v) >> 1, v); return gcd((v - u) >> 1, u); }

int32_t main(){
	SYNC;
	random_device rd;
	mt19937 gen(rd()); // mersenne twister (only for 32 bit unsigned numbers)
	uniform_int_distribution<int> dis(1, 10000); // dis(L, R) uniformly generates [L, R] (inclusive)
	
	/* For 64 bit numbers */
	mt19937_64 gen2(rd());
	uniform_int_distribution<LL> dis2((int)1e9 + 7, (int)1e10);
	cout << dis2(gen) << endl << dis2(gen) << endl;
	
	/* Test Code */
	int n; cin >> n;
	uniform_int_distribution<int> Dis(1, n);
	int f[n + 1] = { 0 };
	for(int i = 0; i < 1000; i ++)
		f[Dis(gen)]++;
	for(int i = 1; i <= n; i ++)
		cout << f[i] << endl;
	cerr << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms" << '\n';
	return 0; 
}