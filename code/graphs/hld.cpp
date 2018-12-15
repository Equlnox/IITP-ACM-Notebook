V<V<int> > g;
int N;
V<int> cpar, id, depth, parent;
V<int> chain;

int dfs(int c,int p){
	parent[c] = p;
	depth[c]=depth[p]+1;
	int sz=1;
	auto it=find(g[c].begin(),g[c].end(),p);
	if(it!=g[c].end())
		g[c].erase(it);
	if(g[c].empty())
		return 1;
	int mx=0;
	for(auto &i:g[c]){
		int cur=dfs(i,c);
		sz+=cur;
		if(cur>mx)
			mx=cur,swap(i,g[c][0]);
	}
	return sz;
}

void form_chains(int c, int cp){
	cpar[c] = cp;
	id[c] = (int)chain.size();
	chain.push_back(c);
	for(int i=0;i<(int)g[c].size();i++){
		if(i)
			form_chains(g[c][i], g[c][i]);
		else
			form_chains(g[c][i], cp);
	}
}

void update(int u, int v){
	while(u!=v){
		if(cpar[v] == cpar[u]){
			if(depth[v] < depth[u])
				swap(v,u);
			supdate(0, N - 1, 1, id[u]+1, id[v]);
			v = u;
		}
		else{
			if(depth[cpar[v]] < depth[cpar[u]])
				swap(v,u);
			supdate(0, N - 1, 1, id[cpar[v]], id[v]);
			v = parent[cpar[v]];
		}
	}
}

void preprocess(int r) {
	depth.resize(N);
	depth[r] = 0;
	cpar.resize(N);
	parent.resize(N);
	chain.clear();
	chain.reserve(N);
	id.resize(N);
	dfs(r, r);
	form_chains(r, r);
}
