
int log(int t){
	int res = 1; 
	for(; 1 << res <= t; res++); 
	return res; 
}

void dfs(int u, int p){
	if(p + 1){
		h[u] = h[p] + 1;
	}

	par[u][0] = p; 

	for(int & i : g[u]){
		if(i != p)
			dfs(i, u); 
	}
}

void pLCA(){
	for(int i = 0; i < n; i++)
		for(int j = 1; 1 << j < n; j++)
			par[i][j] = -1; 

	for(int j = 1; 1 << j < n; j++)
		for(int i = 0; i < n; i++)
			if(par[i][j-1] + 1){
				par[i][j] = par[par[i][j-1]][j-1]; 
			}
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
