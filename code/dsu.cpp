class dsu{
	public:
	vector<int> p;
	dsu(int n){
		p.resize(n);
		for(int i=0;i<n;i++)
			p[i]=i;
	}
	int parent(int x){
		return x==p[x]?x:x=parent(p[x]);
	}
	void unite(int x,int y){
		x=parent(x);
		y=parent(y);
		if(x==y)
			return;
		p[x]=y;
	}
	bool check(int x,int y){
		x=parent(x);
		y=parent(y);
		return x==y;
	}
};