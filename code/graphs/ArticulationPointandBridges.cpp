#include <bits/stdc++.h> 

using namespace std; 
const int N = 50; 
int dis[N], low[N], par[N], AP[N],vis[N],tits; 
void update(int u , int i, int child) {
	//For Cut Vertices
	if(par[u] != -1 && low[i] >= dis[u]) AP[u] = true;
	if(par[u] == -1 && child > 1) AP[u] = true;
	
	//For Finding Cut Bridge
	if(low[i] > dis[u]){
		//articulation bridge found.
	}
}
void dfs(int u){
	vis[u] = true;
	low[u] = dis[u] = (++tits); int child = 0;
	for(int i : g[u]) {
		if(!vis[i]){
			child++;
			par[i] = u;
			dfs(i);
			low[u] = min(low[u] , low[i]);
			update(u, i, child);
		}
		else if(i != par[u]) {
			low[u] = min(low[u] , dis[i]);
		}
	}
}