class FindBridges {
	/**
	 * 	Call with the constructor FindBridges(graph, number_of_nodes).
	 * 	Method find_bridges() returns a vector of pairs, depicting the edges that are bridges.
	 * 	Change the IS_BRIDGE() function and the vector 'bridges' if bridges are required in a different format.
	 * */
  public:
	int n; // number of nodes
	vector<int> *adj;

	vector<bool> visited;
	vector<int> tin, low;
	vector<pair<int, int>> bridges;
	int timer;

	FindBridges(vector<int> *graph, int number_of_nodes) {
		n = number_of_nodes, adj = graph;
	}

	void IS_BRIDGE(int u, int v) {
		// Mark the edge from u to v as a bridge.
		bridges.pb({u, v});
	}

	void dfs(int v, int p = -1) {
		visited[v] = true;
		tin[v] = low[v] = timer++;
		for (int to : adj[v]) {
			if (to == p) {
				continue;
			}
			if (visited[to]) {
				low[v] = min(low[v], tin[to]);
			} else {
				dfs(to, v);
				low[v] = min(low[v], low[to]);
				if (low[to] > tin[v])
					IS_BRIDGE(v, to);
			}
		}
	}

	vector<pair<int, int>> find_bridges() {
		timer = 0;
		visited.assign(n, false);
		tin.assign(n, -1);
		low.assign(n, -1);
		bridges.clear();
		for (int i = 0; i < n; ++i) {
			if (!visited[i])
				dfs(i);
		}
		return bridges;
	}
};
