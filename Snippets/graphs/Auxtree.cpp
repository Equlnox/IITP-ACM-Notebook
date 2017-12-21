#include <bits/stdc++.h>

using namespace std;

int32_t main() {
	//std::vector<int> a contains vertices to form the aux t
	sort(ALL(a), [](const int & a, const int & b) -> bool{
		return st[a] < st[b];
	});
	set<int> s(a);
	for(int i = 0, k = (int)a.size(); i + 1 < k; i++){
		int v = lca(a[i], a[i + 1]);
		if(s.find(v) == s.end())
			a.push_back(v); 
		s.insert(v);
	}

	sort(ALL(a), [](const int & a, const int & b) -> bool{
		return st[a] < st[b];
	});

	stack<int> S; 
	S.push(a[0]);

	auto anc = [](int & a, int & b) -> bool{
		return st[b] >= st[a] && en[b] <= en[a];
	};

	for(int i = 1; i < (int)a.size(); i++){
		while(!anc(S.top(), a[i])) S.pop();
		G[S.top()].pp(a[i]);
		G[a[i]].pp(S.top());
		S.push(a[i]);
	}
	//G is the Aux tree
}