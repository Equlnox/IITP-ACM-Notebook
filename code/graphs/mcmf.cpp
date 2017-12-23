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
	void negativeEdges(int s){
		pot.assign(n,inf);
		pot[s]=0;
		for(int j=0;j<n;j++)
			for(int i=0;i<(int)e.size();i++)	if(e[i].f>0 && pot[e[i^1].v]!=inf){
				pot[e[i].v]=min(pot[e[i].v],pot[e[i^1].v]+e[i].c);
		}
	}
	int augment(int s,int t,int fl,V<bool> &v){
		if(s==t)
			return fl;
		v[s]=1;
		for(auto i:g[s])	if(!v[e[i].v] && e[i].f>0 && (pot[s]-pot[e[i].v]+e[i].c)==0){
			int cf=augment(e[i].v,t,min(fl,e[i].f),v);
			if(cf!=0){
				e[i].f-=cf;
				e[i^1].f+=cf;
				return cf;
			}
		}
		return 0;
	}
	void mcf(int s,int t,bool neg=0){
		int cur=0;
		V<bool> vis;
		if(neg)
			negativeEdges(s);
		do{
			vis.assign(n,0);
			flow+=cur;
			cost+=(pot[t]-pot[s]);
			assignPots(s);
			cur=augment(s,t,inf,vis);
		}while(cur);
	}
};
