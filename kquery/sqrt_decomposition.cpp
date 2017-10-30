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
int BS,BN;
pii a[1000010];
int f[1010][100010];
int main(){SYNC
	memset(f,0,sizeof f);
	int n,m;
	cin>>n>>m;
	repn(i,n){
		cin>>a[i].fi;
		a[i].se=i;
	}
	sort(a+1,a+n+1);
	BS=1000;
	BN=n/BS;
	for(int i=0;i<n;i+=BS){
		for(int j=1;j<=BS && i+j<=n;j++){
			f[i/BS][a[j+i].se]++;
		}
		for(int j=1;j<=n;j++){
			f[i/BS][j]+=f[i/BS][j-1];
		}
	}
	while(m--){
		int l,r,k;
		cin>>l>>r>>k;
		for(int i=0;i<=BN;i++){
			if((f[i][r]-f[i][l-1])<k)
				k-=(f[i][r]-f[i][l-1]);
			else{
				int j=i*BS;
				while(k){
					j++;
					if(a[j].se<=r && a[j].se>=l)
						k--;
				}
				cout<<a[j].fi<<"\n";
				break;
			}
		}
	}
	return 0;
} 
