// edmond karp's algorithm // O(V^2.E)
// similar to dinic's from stanford notebook
struct edge {
	int u,v,c,f;
	edge() {}
	edge(int U, int V, int C, int F): u(U), v(V), c(C), f(F) {}
};
int n;
vector<edge> edges;
vvi graph;
// par stores parent in bfs, ptr stores the edge from par[u] -> u
vi par, ptr;
void addEdge(int u, int v, int c) {
	graph[u].pb(edges.size())
	edges.pb(edge(u,v,c,0));
	graph[v].pb(edges.size())
	edges.pb(edge(v,u,0,0));
}
int bfs(int S, int T) {
	par.assign(n+1, -1); ptr.assign(n+1, 0);
	queue<ii> q({mp(S,INF)}); par[S] = S;
	int ret = 0;
	while(!q.empty()) {
		ii curr = q.front(); q.pop();
		if(curr.ff == T) {ret = curr.ss; break;}
		for(int k: graph[curr.ff]) {
			edge &e = edges[k];
			if(par[e.v] == -1 && e.f < e.c) {
				par[e.v] = e.u;
				ptr[e.v] = k;
				q.push(mp(e.v, min(e.c-e.f, curr.ss)));
			}
		}
	}
	if(par[T] == -1) return 0;
	//augment
	int u = T;
	while(u != S) {
		edges[ptr[u]].f += ret;
		edges[ptr[u]^1].f -= ret;
		u = par[u];
	}
	return ret;
}
int flow(int S, int T) {
	int tot = 0;
	// reset
	for(auto & e : edges) e.f = 0;
	while(int cur = bfs(S, T))
		tot += cur;
	return tot;
}