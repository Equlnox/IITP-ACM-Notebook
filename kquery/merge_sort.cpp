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
/* Equinox */
V<pii> a;
int b[20][100000];
void build(int s,int e,int i){
	if(s==e){
		b[i][s]=a[s].se;
		return;
	}
	int m=(s+e)/2;
	build(s,m,i+1);
	build(m+1,e,i+1);
	merge(b[i+1]+s,b[i+1]+m+1,b[i+1]+m+1,b[i+1]+e+1,b[i]+s);
}
int fre(int i,int s,int e,int l, int r){
	return (int)(upper_bound(b[i]+s,b[i]+e+1,r)-lower_bound(b[i]+s,b[i]+e+1,l));
}
int query(int s,int e,int i,int l,int r,int k){
	while(s!=e){
		int m=(s+e)>>1;
		int d=fre(i+1,s,m,l,r);
		if(d>=k){
			e=m;
		}
		else{
			k-=d;
			s=m+1;
		}
		i++;
	}
	return a[s].fi;
}
int main(){SYNC
	int n,m;
	cin>>n>>m;
	a.resize(n);
	rep(i,n){
		cin>>a[i].fi;
		a[i].se=i;
	}
	sort(ALL(a));
	build(0,n-1,0);
	rep(i,m){
		int l,r,k;
		cin>>l>>r>>k;
		l--;r--;
		cout<<query(0,n-1,0,l,r,k)<<"\n";
	}
	return 0;
} 
