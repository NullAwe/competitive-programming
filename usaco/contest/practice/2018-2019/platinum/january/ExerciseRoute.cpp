#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define vp vector<pii>
#define vb vector<bool>

const int SZ = 30;

int n, m;
ll ans;
vvi adj, up;
vp edges;
vi lvl, back, has, st, except, least;
map<pii, int> duo;

inline int jump(int a, int u) {
  for (int i = 0; i < SZ; ++i) if (u & (1 << i)) a = up[a][i];
  return a;
}

struct HLD {

  vi sizes, order, pos, from, t;
  vb heavy;

  HLD() {}

  int dfs(int v, int p, int l) {
    up[v][0] = p, sizes[v] = 1, lvl[v] = l;
    for (int u : adj[v]) if (u != p) sizes[v] += dfs(u, v, l + 1);
    for (int u : adj[v]) if (u != p && sizes[u] > sizes[v] / 2) heavy[u] = true;
    back.push_back(v);
    return sizes[v];
  }

  void dfs2(int v, int p, int f) {
    pos[v] = order.size(), order.push_back(v), from[v] = f;
    if (!heavy[v]) f = order.size();
    for (int u : adj[v]) if (u != p && heavy[u]) dfs2(u, v, f);
    for (int u : adj[v]) if (u != p && !heavy[u]) dfs2(u, v, f);
  }

  void pre() {
    up = vvi(n, vi(SZ)), sizes.resize(n), pos.resize(n), from.resize(n), heavy.resize(n), lvl.resize(n);
    has.resize(n), st.resize(n), except.resize(n), least.resize(n);
    dfs(0, 0, 0), dfs2(0, 0, 0);
    for (int i = 1; i < SZ; ++i) for (int j = 0; j < n; ++j) up[j][i] = up[up[j][i - 1]][i - 1];
  }

  void build() {
    t.resize(2 * n);
    for (int i = 0; i < n; ++i) {
      int v = order[i];
      if (!heavy[v]) continue;
      for (int u : adj[v]) if (u != up[v][0] && heavy[u]) t[i + n] = except[u];
    }
    for (int i = n - 1; i > 0; --i) t[i] = t[2 * i] + t[2 * i + 1];
  }

  inline int qry(int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans += t[l++];
      if (r & 1) ans += t[--r];
    }
    return ans;
  }

  inline int query(int a, int b) {
    int ans = has[b], cur = up[b][0], under = b;
    if (a == b) return ans;
    while (lvl[cur] > lvl[a]) {
      ans += except[under];
      if (!heavy[cur]) {
        under = cur, cur = up[cur][0];
        continue;
      }
      under = cur, cur = up[cur][0];
      if (!heavy[cur]) continue;
      int r = pos[cur] + 1, l = max(pos[a], from[cur]);
      ans += qry(l, r), under = order[l], cur = up[order[l]][0];
    }
    if (cur == a) ans += except[under];
    return ans;
  }
};

HLD hld;

inline int lca(int a, int b) {
  if (lvl[a] > lvl[b]) swap(a, b);
  b = jump(b, lvl[b] - lvl[a]);
  for (int i = SZ - 1; i >= 0; --i) if (up[a][i] != up[b][i]) a = up[a][i], b = up[b][i];
  return a == b ? a : up[a][0];
}

inline void add(int a, int b) {
  if (lvl[a] > lvl[b]) swap(a, b);
  int c = lca(a, b), d = jump(b, lvl[b] - lvl[c] - 1);
  ++st[d];
  if (a != c) {
    int e = jump(a, lvl[a] - lvl[c] - 1);
    ++st[e];
    ++duo[{d, e}], ++duo[{e, d}];
  }
  ++least[a], ++least[b];
}

void pre() {
  hld.pre();
  for (pii p : edges) ++has[lca(p.first, p.second)], add(p.first, p.second);
  for (int v : back) for (int u : adj[v]) if (u != up[v][0]) has[v] += has[u], least[v] += least[u];
  for (int v = 0; v < n; ++v) except[v] = has[up[v][0]] - has[v] - st[v];
  hld.build();
}

inline int g(int a, int b) {
  return edges.size() - least[a] - least[b] + has[a] + has[b] + duo[{a, b}];
}

inline void sub(int a, int b) {
  if (lvl[a] > lvl[b]) swap(a, b);
  int c = lca(a, b), d = jump(b, lvl[b] - lvl[c] - 1);
  ans -= hld.query(d, b);
  if (a != c) {
    int e = jump(a, lvl[a] - lvl[c] - 1);
    ans -= hld.query(e, a) + g(d, e);
  } else ans -= edges.size() - least[d] + has[d];
}

int main() {
  ifstream in("exercise.in");
  ofstream out("exercise.out");
  in >> n >> m; m -= n - 1;
  ans = (ll) m * (m - 1);
  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; in >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  edges.resize(m);
  for (int i = 0; i < m; ++i) {
    int a, b; in >> a >> b; --a, --b;
    edges[i] = {a, b};
  }
  pre();
  for (pii p : edges) sub(p.first, p.second);
  out << ans / 2 << '\n';
  return 0;
}
