#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef pair<int, int> pii;

struct DSU {
  vector<int> p, sz;
  DSU(int n) {
    p.resize(n), sz.resize(n);
    for (int i = 0; i < n; ++i) p[i] = i, sz[i] = 1;
  }
  int find(int v) {
    if (p[v] == v) return v;
    return p[v] = find(p[v]);
  }
  void join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    p[v] = u, sz[u] += sz[v];
  }
};

const int MOD = 1e9 + 7;

vector<vector<pii>> adj;
vector<int> xors;

const int d = 62;
vector<vector<int>> basis;
vector<int> sz;

void insertVector(int mask, int j) {
  if (basis[j].empty()) basis[j].resize(d);
  for (int i = d - 1; i >= 0; --i) {
    if (!(mask & (1LL << i))) continue;
    if (!basis[j][i]) {
      basis[j][i] = mask;
      ++sz[j];
      return;
    }
    mask ^= basis[j][i];
  }
}

void dfs(int v, int p, int x) {
  xors[v] = x;
  for (pii e : adj[v]) {
    int u = e.first, w = e.second;
    if (u == p) continue;
    dfs(u, v, x ^ w);
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  adj.resize(n);
  DSU dsu(n);
  DSU dsu2(n);
  basis.resize(n);
  sz.resize(n);
  vector<vector<int>> extra;
  for (int i = 0; i < m; ++i) {
    int u, v, w; cin >> u >> v >> w; --u, --v;
    if (dsu.find(u) == dsu.find(v)) {
      extra.push_back({u, v, w});
      continue;
    }
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
    dsu.join(u, v);
    dsu2.join(u, v);
  }
  for (int i = 0; i < n; ++i) {
    if (dsu2.find(i) != dsu2.find(0)) {
      adj[0].push_back({i, 0});
      adj[i].push_back({0, 0});
      dsu2.join(0, i);
    }
  }
  xors.resize(n);
  dfs(0, 0, 0);
  for (vector<int> ex : extra) {
    int u = ex[0], v = ex[1], w = ex[2];
    insertVector(xors[u] ^ xors[v] ^ w, dsu.find(u));
  }
  int ans = 0;
  vector<int> bases(n);
  for (int i = 0; i < n; ++i) {
    int xx = 0;
    for (int j : basis[i]) xx |= j;
    bases[i] = xx;
  }
  vector<vector<int>> groups(n);
  for (int i = 0; i < n; ++i) groups[dsu.find(i)].push_back(i);
  for (int i = 0; i < d; ++i) {
    vector<bool> vis(n);
    for (int v = 0; v < n; ++v) {
      if (vis[v]) continue;
      int pp = dsu.find(v);
      int ssz = dsu.sz[pp];
      bool has = bases[pp] & (1LL << i);
      vector<int> count(2);
      for (int ll : groups[pp]) ++count[(xors[ll] >> i) & 1], vis[ll] = true;
      if (has) ans = (ans + (1LL << i) % MOD * ((ssz * (ssz - 1) / 2) % MOD) % MOD * ((1LL << (sz[pp] - 1)) % MOD) % MOD) % MOD;
      else ans = (ans + (1LL << i) % MOD * count[0] % MOD * count[1] % MOD * ((1LL << (sz[pp])) % MOD) % MOD) % MOD;
    }
  }
  cout << ans << '\n';
  return 0;
}