// from stanford notebook
struct edge {
	int u, v;
	ll c, f;
	edge() { }
	edge(int _u, int _v, ll _c, ll _f = 0): u(_u), v(_v), c(_c), f(_f) { }
};
int n;
vector<edge> edges;
vector<vector<int> > g;
vector<int> d, pt;

void addEdge(int u, int v, ll c, ll f = 0) {
	g[u].emplace_back(edges.size());
	edges.emplace_back(edge(u,v,c,f));
	g[v].emplace_back(edges.size());
	edges.emplace_back(edge(v,u,0,0));
}
bool bfs(int s, int t) {
	queue<int> q({s});
	d.assign(n+1, n+2);
	d[s] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		if (u == t) break;
		for(int k : g[u]) {
			edge &e = edges[k];
			if(e.f < e.c && d[e.v] > d[e.u] + 1){
				d[e.v] = d[e.u] + 1;
				q.push(e.v);
			}
		}
	}
	return d[t] < n+2;
}

ll dfs(int u, int t, ll flow = -1) {
	if(u == t || !flow) return flow;
	for(int &i = pt[u]; i < (int)(g[u].size()); i++) {
		edge &e = edges[g[u][i]], &oe=edges[g[u][i]^1];
		if(d[e.v] == d[e.u] + 1) {
			ll amt = e.c - e.f;
			if (flow != -1 && amt > flow) amt = flow;
			if(ll pushed = dfs(e.v,t,amt)) {
				e.f += pushed;
				oe.f -= pushed;
				return pushed;
			}
		}
	}
	return 0;
}

ll flow(int s, int t) {
	ll ans = 0;
	while(bfs(s,t)) {
		pt.assign(n+1, 0);
		while(ll val = dfs(s,t)) ans += val;
	}
	return ans;
}
