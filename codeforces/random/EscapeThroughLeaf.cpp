#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }

	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}

	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}

	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

vector<int> a, b;
vector<vector<int>> adj;
vector<ll> dp;
vector<LineContainer> chs;

void dfs(int v, int p) {
  for (int u : adj[v]) if (u != p) dfs(u, v);
  int count = 0;
  for (int u : adj[v]) {
    if (u == p) continue;
    if (chs[u].size() > chs[v].size()) swap(chs[u], chs[v]);
    ++count;
    for (Line line : chs[u]) {
      chs[v].add(line.k, line.m);
    }
  }
  if (count == 0) dp[v] = 0;
  else dp[v] = -chs[v].query(a[v]);
  chs[v].add(-b[v], -dp[v]);
}

int32_t main() {
  int n; cin >> n;
  a.resize(n), b.resize(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y; cin >> x >> y; --x, --y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dp.resize(n), chs.resize(n);
  dfs(0, 0);
  for (ll num : dp) cout << num << ' ';
  cout << '\n';
  return 0;
}