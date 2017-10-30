#include <bits/stdc++.h>
using namespace std;
typedef long long				ll;
typedef pair<int,int >			pii;
#define V						vector
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
/* cent Ï */
int n;
int ln;
int d[1000];
int p[1000][10];
V<int> g[1000];
int bits(int x){
	int r=0;
	while(x){
		r++;
		x>>=1;
	}
	return r;
}
void dfs(int i,int dep){
	d[i]=dep;
	for(auto j:g[i])
		dfs(j,dep+1);
}
int lca(int u,int v){
	if(d[u]>d[v])
		swap(u,v);
	int c=ln;
	while(c--){
		if(d[v]-d[u] >= (1<<c))
			v=p[v][c];	
	}
	if(v==u)
		return u;
	c=ln;
	while(c--){
		if(p[u][c]!=p[v][c]){
			u=p[u][c];
			v=p[v][c];
		}
	}
	return p[u][0];
}
int main(){SYNC
	int T;
	cin>>T;
	p[0][0]=0;
	repn(tc,T){
		cout<<"Case "<<tc<<":\n";
		cin>>n;
		rep(i,n){
			g[i].clear();
			int x;
			cin>>x;
			rep(j,x){
				int c;
				cin>>c;
				g[i].pb(c-1);
				p[c-1][0]=i;
			}
		}	
		for(int i=1;1<<i < n;i++)
			for(int j=0;j<n;j++)
				p[j][i]=p[p[j][i-1]][i-1];
		ln=bits(n-1);
		dfs(0,0);
		int q;
		cin>>q;
		while(q--){
			int u,v;
			cin>>u>>v;
			cout<<lca(u-1,v-1)+1<<"\n";
		}
	}
	return 0;
} 
