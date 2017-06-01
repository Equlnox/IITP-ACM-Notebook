// maximum cardinality bipartite matching using augmenting paths.
// assumes that first n elements of graph adjacency list belong to the left vertex set.
int n;
vector<vector<int>> graph;
vector<int> match, vis;

int augment(int l) {
	if(vis[l]) return 0;
	vis[l] = 1;
	for(auto r: graph[l]) {
		if(match[r]==-1 || augment(match[r])) {
			match[r]=l; return 1;
		}
	}
	return 0;
}

int matching() {
	int ans = 0;
	for(int l = 0; l < n; l++) {
		vis.assign(n, 0);
		ans += augment(l);
	}
	return ans;
}
