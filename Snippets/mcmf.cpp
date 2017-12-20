#include <bits/stdc++.h>
using namespace std;
typedef long long				ll;
typedef pair<int,int >			pii;
template<typename T>
using V = vector<T>;
#define SYNC					ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i,b)				for(int i=0;i<b;i++)
#define repn(i,n)				for(int i=1;i<=n;i++)
#define ALL(x)					(x).begin(),(x).end()
#define fi						first
#define se						second
#define pb						push_back
#define dzx						cerr<<"here";
const ll MOD=1e9+7,INF=0x3F3F3F3F3F3F3F3F;
const int inf=0x3F3F3F3F;
/* Equinox */
int tt=0;
class CostFlowGraph{
public:
	struct Edge{	
		int v,f,c;
		Edge(){}
		Edge(int v,int f,int c):v(v),f(f),c(c){}
	};
	V<V<int> > g;
	V<Edge> e;
	V<int> pot;
	int n;
	int flow;
	int cost;
	CostFlowGraph(int sz){
		n=sz;
		g.resize(n);
		pot.assign(n,0);
		flow=0;
		cost=0;
	}
	void clear(){
		flow=0;cost=0;
		for(int i=0;i<(int)e.size();i++){
			e[i].f+=e[i^1].f;
			e[i^1].f=0;
		}
	}
	void addEdge(int u,int v,int cap,int c){
		g[u].pb((int)e.size());
		e.pb(Edge(v,cap,c));
		g[v].pb((int)e.size());
		e.pb(Edge(u,0,-c));	
	}
	void assignPots(int s){
		priority_queue<pii,V<pii>,greater<pii>> q;
		V<int> npot(n,inf);
		q.push({s,0});
		while(!q.empty()){
			auto cur=q.top();q.pop();
			if(npot[cur.fi]<=cur.se)
				continue;
			npot[cur.fi]=cur.se;
			for(auto i:g[cur.fi])	if(e[i].f>0){
				int cst=pot[cur.fi]-pot[e[i].v]+e[i].c;
				q.push({e[i].v,cst+cur.se});
			}
		}
		for(int i=0;i<n;i++)	if(npot[i]!=inf){
			pot[i]+=npot[i];
		}
	}
	void dfs(int t,V<bool> &v,V<int> &stk){
		auto cur=stk.back();
		v[e[cur].v]=1;
		if(e[stk.back()].v==t)
			return ;
		for(auto i:g[e[cur].v])	if(!v[e[i].v] && e[i].f>0 && (pot[e[cur].v]-pot[e[i].v]+e[i].c)==0){
			stk.pb(i);
			dfs(t,v,stk);
			if(e[stk.back()].v==t)
				return ;
		}
		stk.pop_back();
	}
	int augment(int s,int t){
		V<bool> v(n,false);
		vector<int> stk;
		if(g[s].size()==0)
			return 0;
		stk.pb(g[s][0]^1);
		dfs(t,v,stk);
		if(stk.empty())
			return 0;
		int mx=inf;
		for(int i=1;i<(int)stk.size();i++)
			mx=min(mx,e[stk[i]].f);
		for(int i=1;i<(int)stk.size();i++){
			e[stk[i]].f-=mx;
			e[(stk[i])^1].f+=mx;
		}
		return mx;
	}
	void mcf(int s,int t){
		int cur=0;
		do{
			flow+=cur;
			cost+=(pot[t]-pot[s]);
			assignPots(s);
			cur=augment(s,t);
		}while(cur);
	}
};
int32_t main(){SYNC
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		V<int> fre(n+1,0);
		CostFlowGraph cg(n+2);
		repn(i,n){
			int x;
			cin>>x;
			fre[x]++;
		}
		repn(i,n){
			cg.addEdge(i,n+1,1,0);
			cg.addEdge(0,i,fre[i],0);
		}
		int e;
		cin>>e;
		while(e--){
			int x,y;
			cin>>x>>y;
			cg.addEdge(x,y,n,1);
			cg.addEdge(y,x,n,1);
		}
		cg.mcf(0,n+1);
		cout<<cg.cost<<"\n";
	}
	return 0;
}