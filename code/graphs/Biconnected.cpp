#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 10;
 
vector<vector<int>> tree, g; 
bool isBridge[N << 2], vis[N]; 
int Time, arr[N], U[N], V[N], cmpno, comp[N]; 
vector<int> temp; //temp stores component values
 
int adj(int u, int e){
	return (u == U[e] ? V[e] : U[e]); 
}
 
int find_bridge(int u , int edge){
	vis[u] = true; 
	arr[u] = Time++; 
	int x = arr[u]; 
 
	for(auto & i : g[u]){
		int v = adj(u, i);
		if(!vis[v]){
			x = min(x,find_bridge(v, i)); 
		} 
		else if(i != edge){
			x = min(x,arr[v]); 
		}
	}
 
	if(x == arr[u] && edge != -1){
		isBridge[edge] = true; 
	}
	return x; 
}

void dfs1(int u){
	int current = cmpno; 
	queue<int> q;
	q.push(u);  
	vis[u] = 1;
	temp.push_back(current); 
 
	while(!q.empty()){
		int v = q.front(); 
		q.pop(); 
		comp[v] = current; 
 
		for(auto & i : g[v]) {
			int w = adj(v, i); 
			if(vis[w])continue; 
			if(isBridge[i]){
				cmpno++; 
				tree[current].push_back(cmpno); 
				tree[cmpno].push_back(current); 
				dfs1(w); 
			}
			else{
				q.push(w); 
				vis[w] = 1; 
			}
		}
	}
}

int main(){
	int n, m;
	cin >> n >> m; 
	g.resize(n + 2); tree.resize(n + 2);

	for(int i = 0; i < m; i ++){
		cin >> U[i] >> V[i]; 
		g[U[i]].push_back(i); 
		g[V[i]].push_back(i);  
	}

	cmpno = Time = 0; 
	memset(vis, false, sizeof vis); 
	
	for(int i = 0; i < n; i ++){
		if(!vis[i]){
			find_bridge(i , -1); 
		}
	}

	memset(vis, false, sizeof vis); 
	cmpno = 0;
	
	for(int i = 0; i < n; i ++){
		if(!vis[i]){
			temp.clear(); 
			cmpno++; 
			dfs1(i);
		}
	}
}