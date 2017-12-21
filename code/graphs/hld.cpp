int n;
V<V<P<int>> > g;
V<int> values;
V<int> depth;
V<int> size;
V<int> hchild;
V<V<int> > chains;
V<int> head;
V<int> cmap,idmap;
V<int> parent;
V<P<int> > Edges;
V<Segtree> trees;
void dfs(int u,int p){
	parent[u]=p;
	depth[u]=depth[p]+1;
	size[u]=1;
	int hs=0,hv=-1;
	for(auto v:g[u])	if(v.fi!=p){
		dfs(v.fi,u);
		values[v.fi]=v.se;
		size[u]+=size[v.fi];
		if(size[v.fi]>hs){
			hv=v.fi;
			hs=size[v.fi];;
		}
	}
	hchild[u]=hv;
}
void form(int u,int p){
	cmap[u]=(int)chains.size()-1;
	idmap[u]=(int)chains.back().size();
	if(chains.back().size()==0){
		head.pb(u);
	}
	chains.back().pb(values[u]);
	if(hchild[u]!=-1)
		form(hchild[u],u);
	for(auto v:g[u])	if(v.fi!=p && v.fi!=hchild[u]){
		chains.pb({});
		form(v.fi,u);
	}
}
void build(){
	for(int i=0;i<chains.size();i++){
		trees.pb(Segtree(chains[i]));
	}
}
int query(int u,int v){
	int r=0;
	while(u!=v){
		if(cmap[v]==cmap[u]){
			if(depth[v]<depth[u])
				swap(v,u);
			r=max(r,trees[cmap[v]].query(idmap[u]+1,idmap[v]));
			v=u;
		}
		else{
			if(depth[head[cmap[v]]]<depth[head[cmap[u]]])
				swap(v,u);
			int h=head[cmap[v]];
			int hid=idmap[h];
			int vid=idmap[v];
			r=max(r,trees[cmap[v]].query(hid,vid));
			v=parent[h];
		}
	}
	return r;
}
void update(int idx,int val){
	auto p=Edges[idx-1];
	int v=p.se;
	if(depth[p.se]<depth[p.fi])
		v=p.fi;
	trees[cmap[v]].update(idmap[v],val);
}
