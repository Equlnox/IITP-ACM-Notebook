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

#define time ____lkjdlajkf
const int N = (int)2e5 + 10;
int st[N], time = 0, en[N], h[N];

class LCA{
public:
	int n;
	V<V<int>> g, par;
	
	LCA(V<V<int>> & g, int n){
		this->g = g; 
		this->n = n;
		par.resize(n, V<int>(log(n), -1));
		pLCA();
	}

	int log(int & t){
		int ans; 
		for(ans = 1; (1 << ans) <= t; ans++);
		return ans;
	}

	void dfs(int u, int p){
		st[u] = time++;
		if(p + 1) h[u] = h[p] + 1;
		par[u][0] = p; 

		for(int & i : g[u]) if(i != p) 
			dfs(i, u);
		en[u] = time;
	}

	void pLCA(){
		dfs(0, -1);
		for(int j = 1; 1 << j < n; j++){
			for(int i = 0; i < n; i++)
				if(par[i][j - 1] + 1)
					par[i][j] = par[par[i][j - 1]][j - 1];
		}
	}

	int lca(int u, int v){
		if(h[u] < h[v]) swap(u, v);
		int l = log(h[u]); 

		for(int i = l - 1; i >= 0; i--){
			if(par[u][i] + 1 && h[u] - (1 << i) >= h[v]){
				u = par[u][i];
			}
		}

		if(v == u) return v;

		for(int i = l - 1; i >= 0; i--){
			if(par[u][i] + 1 && par[u][i] != par[v][i]){
				u = par[u][i]; 
				v = par[v][i];
			}
		}

		return par[u][0];
	}
};

V<V<int>> g, G;
int n, q;
bool mark[N];
#define int long long
const int MOD = (int)1e9 + 7;

int multiply(int a, int b){
	LL x = a * 1LL * b;
	return (x >= MOD ? x % MOD : x);
}

P<int,int> _dfs(int u, int p, int & ans){
	P<int,int> temp = {0, 0};
	int a = (u + 1) * 1LL * (h[u]);
	a %= MOD; 
	int b = (u + 1);

	for(int i : G[u]){
		if(i != p){
			auto j = _dfs(i, u, ans);
			ans = (ans + multiply(j.fi, temp.se) + multiply(j.se, temp.fi));
			ans = (ans - multiply(2, multiply(h[u], multiply(j.se, temp.se))));
			ans %= MOD; 
			ans = (ans + MOD) % MOD;
			temp.fi += j.fi; 
			temp.se += j.se;
			check(temp.fi,  MOD);
			check(temp.se, MOD);
		}
	}

	if(mark[u]){
		ans = (ans + multiply(a, temp.se) + multiply(b, temp.fi));
		ans = (ans - multiply(2, multiply(h[u], multiply(b, temp.se))));
		ans = (ans % MOD + MOD) % MOD; 
		temp.fi += a;
		temp.se += b;
		check(temp.fi, MOD);
		check(temp.se, MOD);
	}
	return temp;
}

int32_t main(){
	SYNC; 
	cin >> n >> q; 
	g.resize(n);

	REP(i, n - 1){
		int a, b; 
		cin >> a >> b; 
		a--; b--; 
		g[a].pp(b); 
		g[b].pp(a);
	}

	LCA lca(g, n);
	G.resize(n);

	while(q--){
		int k; 
		cin >> k; 
		V<int> a(k);
		set<int> s;

		REP(i, k){
			cin >> a[i];
			a[i]--;
			s.insert(a[i]);
			mark[a[i]] = 1;
		}
		sort(ALL(a), [](const int & a, const int & b) -> bool{
			return st[a] < st[b];
		});

		for(int i = 0; i + 1 < k; i++){
			int v = lca.lca(a[i], a[i + 1]);
			if(s.find(v) == s.end())
				a.pp(v); 
			s.insert(v);
		}

		sort(ALL(a), [](const int & a, const int & b) -> bool{
			return st[a] < st[b];
		});

		stack<int> S; 
		S.push(a[0]);

		auto anc = [](int & a, int & b) -> bool{
			return st[b] >= st[a] && en[b] <= en[a];
		};

		for(int i = 1; i < (int)a.size(); i++){
			while(!anc(S.top(), a[i])) S.pop();
			G[S.top()].pp(a[i]);
			G[a[i]].pp(S.top());
			S.push(a[i]);
		}int ans = 0;

		_dfs(a[0], -1, ans);

		for(int i : a){
			G[i].clear();
			mark[i] = false;
		}

		cout << ans << endl; 
	}

	cerr << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms" << '\n';
	return 0; 
}