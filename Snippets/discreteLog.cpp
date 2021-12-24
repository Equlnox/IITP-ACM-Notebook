class DiscreteLog{
public:
	V<P<LL,int> > table;
	LL a, b, c, g; //find x $ a^x = b (mod g)
	
	DiscreteLog(){}
	DiscreteLog(LL a, LL b, LL g) : a(a), b(b), g(g){}
	
	void initialize(LL g, LL a, V<P<LL,int> > &table, LL &c) {
		LL x = 1;
		int S;
		for(S = 1; S * 1LL * S < g; S++);

		table.resize(S);
		for(int i = 0; i < S; ++ i) {
			table[i] = make_pair(x, i);
			x = mulmod(x, a, g);
		}
		sort(table.begin(), table.end());
		c = powerL(x, g - 2, g); //inverse of x modulo g. 
	}

	LL babyStepGiantStep(LL g, LL b, LL c, LL N, const V<P<LL,int> >&table) {
		int S = table.size(), T = (int)((N + S - 1) / S);
		LL y = b;
		for(int i = 0; i < T; ++ i) {
			auto it = lower_bound(table.begin(), table.end(), make_pair(y, -1));
			if(it != table.end() && it->first == y)
				return i * S + it->second;
			y = mulmod(y, c, g);
		}
		return -1;
	}

	LL find(LL a, LL b, LL g){
		this->a = a; 
		this->b = b; 
		this->g = g;
		initialize(this->g, this->a, this->table, this->c); 
		return babyStepGiantStep(this->g, this->b, this->c, this->g, this->table); 
	}
};