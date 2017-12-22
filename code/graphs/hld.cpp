V<V<int> > g,chains;
V<int> value,cpar,cid,id,depth;
V<SegTree<int>> trees;
int dfs(int c,int p){
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
void form_chains(int c){
	cid[c]=(int)chains.size()-1;
	id[c]=(int)chains.back().size();
	chains.back().pb(value[c]);
	for(int i=0;i<(int)g[c].size();i++){
		if(i)
			chains.pb({}),cpar.pb(c);
		form_chains(g[c][i]);
	}
	if(g[c].empty())
		trees.pb(SegTree<int>([](int a,int b){return max(a,b);},0,(int)chains.back().size(),chains.back()));
}
void update(int v,int val){
	trees[cid[v]].update(id[v],val);
}
int query(int u,int v){
	int r=0;
	while(u!=v){
		if(cid[v]==cid[u]){
			if(depth[v]<depth[u])
				swap(v,u);
			r=max(r,trees[cid[v]].query(id[u]+1,id[v]));
			v=u;
		}
		else{
			if(depth[cpar[cid[v]]]<depth[cpar[cid[u]]])
				swap(v,u);
			r=max(r,trees[cid[v]].query(0,id[v]));
			v=cpar[cid[v]];
		}
	}
	return r;
}
