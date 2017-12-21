class sat_2{
public:
	int n, m, tag;
	V<V<int>> g, grev;
	V<bool> val;
	V<int> st;
	V<int> comp;

	sat_2(){}
	sat_2(int n) : n(n), m(2 * n), tag(0), g(m + 1), grev(m + 1), val(n + 1) { }

	void add_edge(int u, int v) { //u or v
		auto make_edge = [&](int a, int b) {
			if(a < 0) a = n - a;
			if(b < 0) b = n - b;
			g[a].pp(b);
			grev[b].pp(a);
		};

		make_edge(-u, v);
		make_edge(-v, u);
	}

	void truth_table(int u, int v, V<int> t) {
		for(int i = 0; i < 2; i ++) for(int j = 0; j < 2; j ++) {
			if(!t[i * 2 + j])
				add_edge((2 * (i ^ 1) - 1) * u, (2 * (j ^ 1) - 1) * v);
		}
	}

	void dfs(int u, V<V<int>> & G, bool first) {
		comp[u] = tag;
		for(int & i : G[u]) if(comp[i] == -1)
			dfs(i, G, first);
		if(first) st.push_back(u);
	}

	bool satisfiable() {
		tag = 0; comp.assign(m + 1, -1);
		for(int i = 1; i <= m; i ++) {
			if(comp[i] == -1) 
				dfs(i, g, true);
		}reverse(ALL(st));

		tag = 0; comp.assign(m + 1, -1);
		for(int & i : st) {
			if(comp[i] != -1) continue;
			tag++;
			dfs(i, grev, false);
		}

		for(int i = 1; i <= n; i ++) {
			if(comp[i] == comp[i + n]) return false;
			val[i] = comp[i] > comp[i + n];
		}

		return true;
	}
};