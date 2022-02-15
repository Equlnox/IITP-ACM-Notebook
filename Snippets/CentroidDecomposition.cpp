#include <bits/stdc++.h> 

using namespace std; 

const int N = (int)1e5 + 10;
vector<vector<int>> centroid_tree, g;
bool CentMark[N]; int child[N];  

void dfs(int u,int p, bool cond, int & centroid, int nodes){
	child[u] = (cond ? 1 : child[u]);
	bool possible = true;  	
	for(int & i : g[u]){
		if(i != p && !CentMark[i]){
			dfs(i,u, cond, centroid, nodes);
			child[u] += (cond ? child[i] : 0); 
			possible &= (!cond ?((child[i]) <= (nodes/2)): false);
		}
	}
	if(possible && (nodes - child[u]) <= (nodes)/2)
		centroid = u; 
	return;
}

int find_centroid(int src){
	int centroid = -1;
	dfs(src, -1, 1, centroid, 0); 
	dfs(src,-1,0, centroid, child[src]);
	CentMark[centroid] = true; 
	return centroid; 
}

int decompose(int u){
	int centroid = find_centroid(u); 

	for(int & i : g[centroid]){
		if(!CentMark[i]){
			int SubTreeCentroid = decompose(i); 
			centroid_tree[SubTreeCentroid].push_back(centroid); 
			centroid_tree[centroid].push_back(SubTreeCentroid);
		}
	}

	return centroid; 
}

int main(){
	int n; cin >> n;
	g.clear(); g.resize(n + 1); centroid_tree.clear(); centroid_tree.resize(n+1);  
	memset(CentMark, 0 , sizeof CentMark); 

	for(int i = 0; i < n - 1; i++){
		int a, b; cin >> a >> b; 
		g[a].push_back(b); 
		g[b].push_back(a); 
	}

	decompose(1); 
	return 0;
}