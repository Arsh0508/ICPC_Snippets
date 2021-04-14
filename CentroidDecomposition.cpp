#include <bits/stdc++.h>
using namespace std;

class CentroidDecomp {
	/**
	 * Perform centroid decomposition of a tree.

	 * Usage: call constructor as CentroidDecomp(n, g)
	 * 	where n is the no of nodes
	 * 	and g is the tree, either as a vector of vectors,
	 * 		or as an array of vectors.
	 * 
	 * MAKE SURE that g is at least n + 1 in size 
	 * (so it can be indexed from 0 to n inclusive) 
	 * 
	 * Then, calling the CentroidDecomp::decomp(root, -1) 
	 * will generate the centroid decomposition of the tree
	 * in the form of the vector 
		* 	CentroidDecomp::parent,
	 * which represents the parent of each node 
	 * in the centroid tree.
	 * You can then use that as it is, or make the centroid tree
	 * as a graph using those values.
	 * */
	using vi = vector<int>;
	using vvi = vector<vi>;
	int n;
	vi sub;
	vvi g;
	
  public:
	vi parent;
	CentroidDecomp(int n) {
		this -> n = n;
		sub.assign(n + 5, 0);
		g.assign(n + 5, vi());
		parent.assign(n + 5, 0);
	}
	CentroidDecomp(int n, vvi g) : CentroidDecomp(n) {
		this -> g = g;
	}
	CentroidDecomp(int n, vi *g) : CentroidDecomp(n) {
		for (int i = 0; i <= n; ++i) {
			this -> g[i] = g[i];
		}
	}
	// Calculate sizes of subtrees of each node.
	int subsize(int src, int par) {
		sub[src] = 1;
		for (int e: g[src]) {
			if (e != par) {
				sub[src] += subsize(e, src);
			}
		}
		return sub[src];
	}
	// Find the centroid in a subtree.
	int centroid(int src, int par, int n) {
		for (int e: g[src]) {
			if (e != par) {
				if (sub[e] > n / 2) {
					return centroid(e, src, n);
				}
			}
		}
		return src;
	}
	// Decompose a subtree rooted at src into a centroid tree.
	int decomp(int src, int par) {
		int nn = subsize(src, par);
		int c = centroid(src, par, nn);
		if (par == -1) {
			par = c;
		}
		parent[c] = par;
		for (int e: g[c]) {
			g[e].erase(find(g[e].begin(), g[e].end(), c));
			int x = decomp(e, c);
			// You can direct an edge from c to x if you
			// want to create the centroid tree as a graph.
		}
		return c;
	}
};
