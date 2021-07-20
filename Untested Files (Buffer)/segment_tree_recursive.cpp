#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
	/**
	 * 	Segment Tree class that supports lazy updates.
	 * 	Specify the merge operation in the merge() function,
	 * 	and the lazy propagation in the propagate() function.
	 * 
	 * 	Number of leaf nodes for the segment tree, n, is to be passed into the constructor.
	 * 	(Size of the seg tree is then 4 * n).
	 * 	The update() function takes a parameter val, which is assigned to the lazy value
	 * 	of the seg tree nodes and then propagated.
	 **/

	using vi = vector<int>;

	int n;
	vi tree, lazy;
	int IDENTITY = 0; // Identity element of the operation on the segtree.
	// Example: 0 is identity for addition, INF is identity for min(), etc.
	inline int left(int v) {
		return 2 * v;
	}
	inline int right(int v) {
		return 2 * v + 1;
	}
	inline int merge(int lhs, int rhs) {
		// This function dictates the merge operation over the segment tree.
		return lhs + rhs;
	}
	inline void propagate(int v, int tl, int tr) {
		if (lazy[v] != IDENTITY) {
			tree[v] += lazy[v] * (tr - tl + 1);
		}
		if (tl != tr) {
			lazy[left(v)] += lazy[v];
			lazy[right(v)] += lazy[v];
		}
		lazy[v] = 0;
	}
  public:
  	SegmentTree(int N) {
		n = N;
  		tree.assign(4 * N, 0);
  		lazy.assign(4 * N, 0);
  	}
	void build(vi &a, int v, int tl, int tr) {
		if (tl == tr) {
			tree[v] = a[tl];
		} else {
			int tm = (tl + tr) >> 1;
			build(a, left(v), tl, tm);
			build(a, right(v), tm + 1, tr);
			tree[v] = merge(tree[left(v)], tree[right(v)]);
		}
	}
	int query(int v, int tl, int tr, int ql, int qr) {
		propagate(v, tl, tr);

		if (qr < tl || tr < ql)
			return IDENTITY;
		if (ql <= tl && tr <= qr)
			return tree[v];

		int tm = (tl + tr) >> 1;
		return merge(query(left(v), tl, tm, ql, qr), query(right(v), tm + 1, tr, ql, qr));
	}
	void update(int v, int tl, int tr, int ql, int qr, int val) {
		propagate(v, tl, tr);

		if (qr < tl || tr < ql)
			return;
		if (ql <= tl && tr <= qr) {
			lazy[v] = val;
			propagate(v, tl, tr);
			return;
		}
		int tm = (tl + tr) >> 1;
		update(left(v), tl, tm, ql, qr, val);
		update(right(v), tm + 1, tr, ql, qr, val);
		tree[v] = merge(tree[left(v)], tree[right(v)]);
	}
};
