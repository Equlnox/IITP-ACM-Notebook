#include <bits/stdc++.h>

using namespace std;

using LL = long long;
template<typename T> using V = vector<T>; 
template<typename T, typename S> using P = pair<T, S>; 
template<class T> using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;
using LD = long double;

#define ALL(v) v.begin(), v.end()
#define en(v) *(--v.end())
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

template<class TH> void _dbg(const char *sdbg, TH h){cerr<<sdbg<<"="<<h<<"\n";}
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
	while(*sdbg!=','){cerr<<*sdbg++;} cerr<<"="<<h<<","; _dbg(sdbg+1, a...);
}

#ifdef aishwarya_tandon_is_the_best
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

V<int> A{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

long long mulmod(long long a, long long b, long long mod) {
	long long ans = 0;
	if(a >= mod) a %= mod;
	if(b >= mod) b %= mod;
	while(b) {
		if(b & 1) ans = (ans + a) % mod;
		a = (a * 2) % mod;
		b >>= 1;
	}
	return ans;
}

long long power(long long a, long long b, long long mod) {
	long long ans = 1;
	while(b) {
		if(b & 1) ans = mulmod(ans, a, mod);
		a = mulmod(a, a, mod);
		b >>= 1;
	}
	return ans;
}

bool Miller(long long p){
	if(p < 2){
		return false;
	}
	if(p != 2 && p % 2 == 0){
		return false;
	}
	long long s = p - 1;
	while(s % 2 == 0){
		s /= 2;
	}
	for(auto & a : A){
		long long temp = s;
		long long mod = power(a, temp, p);
		while(temp != p - 1 && mod != 1 && mod != p-1){
			mod = mulmod(mod, mod, p);
			temp *= 2;
		}
		if(mod != p - 1 && temp % 2 == 0){
			return false;
		}
	}
	return true;
}

long long power(long long a, int b) {
	long long ans = 1;
	while(b) {
		if(b & 1) ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

int32_t main() { SYNC
	random_device rd;	
	mt19937_64 gen2(rd());
	LL l = power(10LL, 10LL);
	LL r = power(10LL, 11LL);
	uniform_int_distribution<LL> dis2(l, r);

	for(int i = 1; i <= 1000; i ++) {
		LL num = dis2(gen2);
		while(!Miller(num)){
			num = dis2(gen2);
		}
		cout << num << endl;
	}

	cerr << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms" << '\n';
	return 0;	
}