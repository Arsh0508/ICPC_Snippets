//Reference for usage: https://codeforces.com/contest/1215/submission/113814380

using Graph = vector<vector<int>>;

//ONE MAJOR SOURCE OF ERROR: blindly using long long can lead to MLE!

// Struct for finding strongly connected components in a graph
// Condensed graph is in reverse topological order
// "comp" gives component in condensed graph that node i is in
struct SCC {
	Graph g;
	vector<int> comp;
	vector<int> ind;
	vector<int> sta;
	int di = 0; // DFS counter
	int cc = 0; // Comp count

	int dfs(int i) {
		if (ind[i] != -1) return (comp[i] == -1) ? ind[i] : di;
		ind[i] = di;
		int md = di;
		++di;

		sta.push_back(i);
		for (auto t : g[i]) md = min(md, dfs(t));

		if (md == ind[i]) {
			while(comp[i] == -1) {
				comp[sta.back()] = cc;
				sta.pop_back();
			}
			++cc;
		}
		return md;
	}
	SCC(const Graph& gr) : g(gr), comp(gr.size(), -1), ind(gr.size(), -1) {
		for (int i = 0; i < g.size(); ++i) dfs(i);
	}
};

// Struct for solving twosat
// addClause(i, twosat.neg(j)) adds clause i, -j
// solve() returns empty vector if unsolvable
// all this is written assuming 0-based indexing!!!
struct TwoSat {
	const int n;
	Graph g; // Implication graph, of size 2*n

	TwoSat(int nodes) : n(nodes), g(2*nodes) {}

	int neg(int i) {
		return i >= n ? i-n : i+n;
	}

	//wrote it corresponding to or, please change this function accordingly once at the beginning of the question
	void addClause(int a, int b) {
		g[neg(a)].push_back(b);
		g[neg(b)].push_back(a);
	}
	vector<bool> solve() {
		SCC scc(g);

		vector<int> inv(scc.cc);
		for (int i = 0; i < 2*n; ++i) {
			inv[scc.comp[i]] = scc.comp[neg(i)];
		}

		vector<int> state(scc.cc, -1);
		for (int i = 0; i < scc.cc; ++i) {
			if (state[i] != -1) continue;
			if (i == inv[i]) return {};
			state[i] = 1;
			state[inv[i]] = 0;
		}

		vector<bool> res(n);
		for (int i = 0; i < n; ++i) res[i] = state[scc.comp[i]];
		return res;
	}
};
