// This code solves problem Help Ashu on hackerearth 
// Iterative segment tree supporting non commutative combiner function
// The combiner function and identity of the combiner function are taken as contructor arguments
// Assign the initial input into t[size] to t[2*size-1] then call build
// Memory 2*size*sizeof(T)
// Time complexity O(log(size))
#include <bits/stdc++.h>
using namespace std;
/* Equinox */
template<typename T>
class SegTree{
public:
	vector<T> t;
	T identity;
	T (*combine)(T,T);
	int size;
	SegTree(T (*op)(T,T),T e,int n){
		combine=op;
		identity=e;
		t.assign(2*n,e);
		size=n;
	}
	void build(){for(int i=size-1;i>0;i--)t[i]=combine(t[i<<1],t[i<<1|1]);}
	T query(int l,int r){
		T lt=identity;
		T rt=identity;
		for(l+=size,r+=size;l<=r;r>>=1,l>>=1){
			if(l&1)		lt=combine(lt,t[l++]);
			if(!(r&1))	rt=combine(t[r--],rt);
		}
		return combine(lt,rt);
	}
	void update(int p,T v){for(t[p+=size]=v;p>>=1;)t[p]=combine(t[p<<1],t[p<<1|1]);}
};
int32_t main(){
	int n;
	cin>>n;
	SegTree<int> tree([](int a,int b){return a+b;},0,n);
	for(int i=0;i<n;i++){
		int a;
		cin>>a;
		tree.t[i+n]=a&1;
	}
	tree.build();
	int q;
	cin>>q;
	while(q--){
		int c,x,y;
		cin>>c>>x>>y;
		switch(c){
			case 0:
			tree.update(x-1,y&1);
			break;
			case 1:
			cout<<(y-x+1)-tree.query(x-1,y-1)<<"\n";
			break;
			case 2:
			cout<<tree.query(x-1,y-1)<<"\n";
		}
	}
	return 0;
}
