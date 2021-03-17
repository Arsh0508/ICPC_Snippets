#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define FASTIO
// #define endl "\n"  // Since endl forces a buffer flush which slows down large I/O operations.
#define int long long
#define ff first
#define ss second
#define pb push_back
#define input(c, n) for (int i = 0; i < n; ++i) cin >> c[i];
#define exit_message(s) return 0 * printf(s)
#define show_all(c) for (auto i: c) cout << i << " "; cout << "\n";
#define display(c, a, n) cout << "Displaying array \"" << #c << "\" : \n"; for (int (i) = (a); (i) < (n); ++(i)) cout << (c)[(i)] << " "; cout << "\n";
#define forl(i, a, n) for (int i = (a); (i) < (n); ++(i))
#define dugbe(k) cerr << "-\t> " << #k << " = " << k << "\n";
#define dugbev(arr, idx) cerr << "-\t " << #arr << "[" << idx << "] : " << arr[idx] << "\n";
#define debug(args...) { string _debug_list = #args; replace(_debug_list.begin(), _debug_list.end(), ',', ' '); stringstream _debug_stream(_debug_list); istream_iterator<string> __it(_debug_stream); debug_func(__it, args); }

/*
 * What follows is a magical ordered set data structure.
 * Supports the following functions:
 * find_by_order(int k) - returns k'th smallest element (0-indexed)
 * order_of_key(int k) - returns number of elements strictly smaller than k.
using namespace __gnu_pbds;
#define ordered_set tree <ll, null_type, greater_equal <ll>, rb_tree_tag, tree_order_statistics_node_update>
*/

/* TIPS FOR DEBUGGING
 * Check if values are not overflowing (use long long where required)
 * Check if ranges are inclusive or not.
 * Check properly if greedy will work or not before using it.
 * Check EDGE CASES!! Seriously, even in 2B, saving 8 points by being
 * 2 minutes faster will bite you in the ass if you don't make sure
 * it works on edge cases.
 * Keep adding to this list.
*/

using namespace std;
typedef long long ll;
typedef pair<int, int> pr;
typedef pair<ll, ll> prll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pr> vpr;
typedef vector<vi> vvi;

ifstream in("input.txt");
const ll mod = 1e9 + 7;
const long double eps = 1e-7;
// const long double M_PI = 3.141592653589793238462643383279;

void debug_func(istream_iterator<string> _it)
{
	cerr << "\n";
}

template <typename T, typename... Args>
void debug_func(istream_iterator<string> _it, T x, Args... args)
{
	cerr << "[ " << *_it << " : " << x << " ]";
	cerr << " , ";
	debug_func(++_it, args...);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

long long true_rand(long long n)
{
	// Returns a random number between 0 and n - 1 inclusive using mt19937.
	uniform_int_distribution<long long> uid(0, n - 1);
	return uid(rng);
}

ll mod_pow(ll a, ll b)
{
	if (b == 0)
		return 1LL;

	ll res = mod_pow(a, b >> 1);
	res = (res * res) % mod;
	if (b & 1LL)
		res = (res * a) % mod;
	
	return res;
}

ll inverse(ll a)
{
	return mod_pow(a, mod - 2);
}

const int N = 1e5 + 5;
const ll INF = 1e9 + 5, LLINF = 1e18 + 5;

vpr ge[N];
vi g[N];
vi parent(N, 0);
vi val(N);
int n, q;

class SegmentTree
{
	/**
	 * 	Segment Tree class that supports lazy updates.
	 * 	Specify the merge operation in the merge() function,
	 * 	and the lazy propagation in the propagate() function.
	 * 	Size of the segment tree is taken to be N by default (N being a global constant).
	 * 	The update() function takes a parameter val, which is assigned to the lazy value
	 * 	of the seg tree nodes and then propagated.
	 **/

	vi tree, lazy;
	int IDENTITY = 0;
	ll MKB = 2147483647;
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
		if (lazy[v]) {
			tree[v] = MKB * (tr - tl + 1) - tree[v];
		}
		if (tl != tr) {
			lazy[left(v)] ^= lazy[v];
			lazy[right(v)] ^= lazy[v];
		}
		lazy[v] = 0;
	}
  public:
  	SegmentTree() {
  		tree.assign(4 * N, 0);
  		lazy.assign(4 * N, 0);
  	}
	void build(vi &a, int v, int tl, int tr) {
		if (tl == tr) {
			tree[v] = a[tl];
		} else {
			int tm = (tl + tr) / 2;
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

		tree[v] = tree[left(v)] + tree[right(v)];
	}
};

class HLD
{
	/**
	 * 	HLD class. Supports build(), query() and update() operations.
	 * 	CALL THE initialize() FUNCTION BEFORE DOING ANYTHING ELSE.
	 * 	Change the merge and propagate functions in the SegmentTree class to achieve the desired functionality.
	 * 	Tree is assumed to be 0-indexed.
	 * 	Build expects a vector of integers (change data types throughout if needed) called 'val' with indexes from 0 to n-1
	 * 	(n being the no. of nodes in the tree) and assigns node i the value val[i].
	 * 	query() and update() work on the path from nodes a to b, as expected.
	 **/

	vi sub, heavy_child, head, pos, depth;
	int cur_pos = 0;
	SegmentTree T;
  public:
  	HLD()
  	{
  		sub.assign(N, 0);
  		heavy_child.assign(N, 0);
  		head.assign(N, 0);
  		pos.assign(N, 0);
  		depth.assign(N, 0);
  		parent.assign(N, 0);
  	}
	void compute_subtree_sizes(int src, int par);
	void decompose(int src, int par, int heavy_id);
	void build(vi &val);
	void initialise();
	int query(int a, int b);
	void update(int a, int b);
	inline int seg_query(int a, int b) {
		return T.query(1, 0, n - 1, a, b);
	}
	inline void seg_update(int a, int b) {
		if (a <= b)
			T.update(1, 0, n - 1, a, b, 1);
	}
};

void HLD :: compute_subtree_sizes(int src, int par)
{
	sub[src] = 1;
	parent[src] = par;
	if (src != par)
		depth[src] = depth[par] + 1;
	int mx = -1;
	for (auto e: g[src])
	{
		if (e == par)
			continue;
		compute_subtree_sizes(e, src);
		sub[src] += sub[e];

		if (mx == -1 || sub[e] > sub[mx])
			mx = e;
	}
	heavy_child[src] = mx;
}

void HLD :: decompose(int src, int par, int heavy_id)
{
	pos[src] = cur_pos++;
	head[src] = heavy_id;
	if (heavy_child[src] != -1)
	{
		decompose(heavy_child[src], src, heavy_id);
	}
	for (auto e: g[src])
	{
		if (e == par || e == heavy_child[src])
			continue;
		decompose(e, src, e);
	}
}

void HLD :: build(vi &val)
{
	vi a(n, -1);
	for (int i = 1; i <= n; ++i) {
		assert (pos[i] < n);
		a[pos[i]] = val[i];
	}
	// cerr << "BUILDING...\n";
	// for (int i = 0; i < n; ++i) {
	// 	assert (a[i] != -1);
	// }
	// cerr << "BUILD DEBUG COMPLETE...\n";
	T.build(a, 1, 0, n - 1);
}

void HLD :: initialise()
{
	cur_pos = 0;
	compute_subtree_sizes(1, 1);
	decompose(1, 1, 1);
	assert (cur_pos == n);
}

int HLD :: query(int a, int b) {
	int res = 0;
	for (; head[a] != head[b]; b = parent[head[b]])
	{
		if (depth[head[a]] > depth[head[b]])
			swap(a, b); // head[a] is now higher than head[b]
		res += seg_query(pos[head[b]], pos[b]);
	}
	if (depth[a] > depth[b])
		swap(a, b); // a is now LCA of original a, b
	res += seg_query(pos[a], pos[b]);
	return res;
}

void HLD :: update(int a, int b) {
	// Perform a segment tree updote on all nodes on the path from a to b.
	for (; head[a] != head[b]; b = parent[head[b]]) {
		if (depth[head[a]] > depth[head[b]])
			swap(a, b);
		seg_update(pos[head[b]], pos[b]);
	}
	if (depth[a] > depth[b])
		swap(a, b);
	seg_update(pos[a], pos[b]);
}

int32_t main()
{
	#ifdef FASTIO
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
	#endif
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	cin >> n >> q;
	vi edges(n - 1, 0);
	forl(i, 0, n - 1)
	{
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}

	for (int i = 1; i <= n; ++i)
	{
		cin >> val[i];
	}

	HLD H;
	H.initialise();
	H.build(val);

	forl(i, 0, q)
	{
		int type, a, b;
		cin >> type >> a >> b;
		if (type == 1) {
			H.update(a, b);
		} else {
			cout << H.query(a, b) << "\n";
		}
	}
	// forl(i, 1, n + 1) {
	// 	ll vloo = H.query(i, i);
	// 	debug(i, vloo);
	// }

	return 0;
}