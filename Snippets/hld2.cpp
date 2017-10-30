#include <bits/stdc++.h>
using namespace std;
typedef long long				ll;
template<typename T>
using V = vector<T>;
template<typename T>
using P = pair<T,T>;
#define SYNC					ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i,b)				for(int i=0;i<b;i++)
#define repn(i,n)				for(int i=1;i<=n;i++)
#define ALL(x)					(x).begin(),(x).end()
#define fi						first
#define se						second
#define pb						push_back
#define dzx						cerr<<"here";
const ll MOD=1e9+7,INF=9e18;
const int inf=2e9;
/* Equinox */
class Segtree{
	public:
	int n;
	Segtree(){}
	Segtree(int n):n(n){
		f.resize(4*n,0);
	}
	Segtree(V<int>& inp){
		n=inp.size();
		f.resize(4*n,0);
		build(0,n-1,1,inp);
	}
	V<int> f;
	void build(int s,int e,int i,V<int> &inp){
		if(s==e){
			f[i]=inp[s];
			return;
		}
		int mid=s+e>>1;
		build(s,mid,i<<1,inp);
		build(mid+1,e,i<<1|1,inp);
		f[i]=max(f[i<<1],f[i<<1|1]);
	}
	void update(int s,int e,int i,int idx,int v){
		if(idx>e || idx<s)
			return;
		if(s==e){
			f[i]=v;
			return;
		}
		int mid=s+e>>1;
		update(s,mid,i<<1,idx,v);
		update(mid+1,e,i<<1|1,idx,v);
		f[i]=max(f[i<<1],f[i<<1|1]);
	}
	int query(int s,int e,int i,int l ,int r){
		if(r<s || l>e)
			return -1;
		if(s>=l && e<=r)
			return f[i];
		int mid=s+e>>1;
		return max(query(s,mid,i<<1,l,r),query(mid+1,e,i<<1|1,l,r));
	}
	void update(int idx,int v){
		update(0,n-1,1,idx,v);
	}
	int query(int l,int r){
		return query(0,n-1,1,l,r);
	}
};
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
int32_t main(){SYNC
	int T;
	cin>>T;
	while(T--){
		g.clear();
		chains.clear();
		head.clear();
		cin>>n;
		trees.clear();
		g.resize(n+1);
		Edges.clear();
		depth.resize(n+1);
		values.resize(n+1);
		size.resize(n+1);
		cmap.resize(n+1);
		idmap.resize(n+1);
		hchild.resize(n+1);
		parent.resize(n+1);
		rep(i,n-1){
			int a,b,c;
			cin>>a>>b>>c;
			g[a].pb({b,c});
			g[b].pb({a,c});
			Edges.pb({a,b});
		}
		depth[0]=-1;
		values[1]=0;
		chains.pb({});
		dfs(1,0);
		form(1,0);
		build();
		string s;
		cin>>s;
		int tt=0;
		while(s != "DONE"){
			int a,b;
			cin>>a>>b;
			if(s=="QUERY"){
				cout<<query(a,b)<<"\n";
			}
			else
				update(a,b);
			cin>>s;
		}
	}
	return 0;
}
