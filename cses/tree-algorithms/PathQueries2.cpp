#include <bits/stdc++.h>
using namespace std;

const int sz = 30;

vector<vector<int>> adj, up;
vector<int> order, parent, level, sizes, m, ps;
vector<bool> heavy;
vector<int> t;
int n;

inline void update(int p, int v) { for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]); }

inline int query(int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = max(ans, t[l++]);
    if (r & 1) ans = max(ans, t[--r]);
  }
  return ans;
}

inline void dfs(int v, int p, int l) {
  parent[v] = p, level[v] = l;
  for (int u : adj[v]) if (u != p) dfs(u, v, l + 1);
  if (v) order.push_back(v);
}

inline void dfs(int v) {
  m[v] = order.size(), order.push_back(v);
  for (int u : adj[v]) if (u != parent[v] && heavy[u]) dfs(u);
  for (int u : adj[v]) if (u != parent[v] && !heavy[u]) dfs(u);
}

inline int lca(int a, int b) {
  if (level[a] < level[b]) swap(a, b);
  for (int i = 0; i < sz; ++i) if ((level[a] - level[b]) & (1 << i)) a = up[a][i];
  if (a == b) return a;
  for (int i = sz - 1; i >= 0; --i) if (up[a][i] != up[b][i]) a = up[a][i], b = up[b][i];
  return up[a][0];
}

inline int qMax(int a, int b) {
  int ans = 0;
  a = m[a], b = m[b];
  while (a >= b) {
    if (heavy[order[a]] && ps[a] <= b) ans = max(ans, query(b, a + 1)), a = b - 1;
    else if (heavy[order[a]]) ans = max(ans, query(ps[a], a + 1)), a = m[parent[order[ps[a]]]];
    else ans = max(ans, t[a + n]), a = m[parent[order[a]]];
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  int q; cin >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  parent.resize(n), level.resize(n); dfs(0, 0, 0);
  up = vector<vector<int>>(n, vector<int>(sz)); for (int i = 0; i < n; ++i) up[i][0] = parent[i];
  for (int i = 1; i < sz; ++i) for (int j = 0; j < n; ++j) up[j][i] = up[up[j][i - 1]][i - 1];
  sizes = vector<int>(n, 1);
  for (int v : order) sizes[parent[v]] += sizes[v];
  heavy.resize(n); for (int i = 0; i < n; ++i) heavy[i] = sizes[i] > sizes[parent[i]] / 2;
  order.clear(), m.resize(n); dfs(0);
  ps.resize(n);
  int last = -1;
  for (int i = 0; i < n; ++i) {
    if (heavy[order[i]] && last < 0) last = i;
    else if (!heavy[order[i]]) last = -1;
    ps[i] = last;
  }
  t.resize(2 * n);
  for (int i = 0; i < n; ++i) update(m[i], arr[i]);
  for (int i = 0; i < q; ++i) {
    int type, a; cin >> type >> a; --a;
    if (type == 1) { int x; cin >> x; update(m[a], x); }
    else {
      int b; cin >> b; --b;
      int p = lca(a, b);
      cout << max(qMax(a, p), qMax(b, p)) << '\n';
    }
  }
  return 0;
}

