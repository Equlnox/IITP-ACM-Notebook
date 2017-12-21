// This code solves problem LITE on spoj 
// Iterative segment tree with lazy propagation supporting non commutative combiner functions
// The combiner function and identity of the combiner function are taken as contructor arguments
// Also the function for application of lazy nodes onto tree nodes is taken as parameter along with Zero of lazy node
// Assign the initial input into t[size] to t[2*size-1] then call build
// Memory 2*size*sizeof(T)+2*size*sizeof(L)
// Time complexity O(log(size))
#include <bits/stdc++.h>
using namespace std;
/* Equinox */
template<typename T,typename L>
class SegTree{
public:
	vector<T> t;
	vector<T> lz;
	T identity;
	L zero;
	T (*combine)(T,T);
	void (*apply)(T&,L&,L&,int k);
	int size;
	int height;
	SegTree(T (*op)(T,T),T e,void (*pro)(T&,L&,L&,int k),L z,int n){
		combine=op;
		apply=pro;
		identity=e;
		zero=z;
		t.assign(2*n,e);
		lz.assign(n,z);
		size=n;
		height = sizeof(int)*8-__builtin_clz(n);
	}
	void build(){for(int i=size-1;i>0;i--)t[i]=combine(t[i<<1],t[i<<1|1]);}
	void push(int p){
		for(int s=height;s>0;s--){
			int i=p>>s;
			apply(t[i<<1],lz[i<<1],lz[i],1<<(s-1));
			apply(t[i<<1|1],lz[i<<1|1],lz[i],1<<(s-1));
			lz[i]=zero;
		}
	}
	void reassign(int p){
		for(p>>=1;p>0;p>>=1)
			if(lz[p]==zero)
				t[p]=combine(t[p<<1],t[p<<1|1]);
	}
	T query(int l,int r){
		push(l+=size);
		push(r+=size);
		T lt=identity;
		T rt=identity;
		for(;l<=r;r>>=1,l>>=1){
			if(l&1)		lt=combine(lt,t[l++]);
			if(!(r&1))	rt=combine(t[r--],rt);
		}
		return combine(lt,rt);
	}
	void update(int p,T v){push(p);for(t[p+=size]=v;p>>=1;)t[p]=combine(t[p<<1],t[p<<1|1]);}
	void update(int l,int r,L v){
		push(l+=size);
		push(r+=size);
		int k=1;
		int l0=l,r0=r;
		for(;l<=r;r>>=1,l>>=1,k<<=1){
			if(l&1)		apply(t[l],lz[l],v,k),l++;
			if(!(r&1))	apply(t[r],lz[r],v,k),r--;
		}
		reassign(l0);
		reassign(r0);
	}
};
int32_t main(){
	int n,m;
	cin>>n>>m;
	SegTree<int,int> s([](int a, int b){return a + b;},0,[](int &v,int &l,int &u,int k){if(u)v=k-v;l^=u;},0,n);
	while(m--){
		int c;
		cin>>c;
		if(!c){
			int l,r;
			cin>>l>>r;
			s.update(l-1,r-1,1);
		}
		else{
			int l,r;
			cin>>l>>r;
			cout<<s.query(l-1,r-1)<<"\n";
		}
	}
	return 0;
}
