void dfs(int u, int p){
	if(p + 1){
		h[u] = h[p] + 1;
		par[u][0].se = cit[p]; 
	}

	par[u][0].fi = p; 

	for(int & i : g[u]){
		if(i != p)
			dfs(i, u); 
	}
}

void pLCA(){
	for(int i = 0; i < n; i++)
		for(int j = 1; 1 << j < n; j++)
			par[i][j].fi = -1; 

	for(int j = 1; 1 << j < n; j++)
		for(int i = 0; i < n; i++)
			if(par[i][j-1].fi + 1){
				par[i][j].fi = par[par[i][j-1].fi][j-1].fi; 
				par[i][j].se = merge(par[i][j-1].se,par[par[i][j-1].fi][j-1].se); 
			}
}