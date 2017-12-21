// 0-based vertex indexing. memset to -1
int log(int t){
	int res = 1; 
	for(; 1 << res <= t; res++); 
	return res; 
}
int lca(int u , int v){
	if(h[u] < h[v])swap(u , v); 
	int L = log(h[u]);
	for(int i = L - 1; i >= 0; i--){
		if(par[u][i] + 1 && h[u] - (1 << i) >= h[v])
			u = par[u][i]; 
	}
	if(v == u) return u;
	for(int i = L - 1; i >= 0; i--){
		if(par[u][i] + 1 && par[u][i] != par[v][i]){ 
			u = par[u][i]; v = par[v][i]; 
		}
	}
	return par[u][0];
}
