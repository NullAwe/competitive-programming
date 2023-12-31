#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MOD = 1e9 + 7;
const int INV2 = 500000004;

inline ll p(ll x, ll y) {
  ll res = 1;
  while (y) {
    if (y & 1) res = res * x % MOD;
    x = x * x % MOD;
    y >>= 1;
  }
  return res;
}

inline ll inv(ll x) {
  return p(x, MOD - 2);
}

struct DSU {

  vector<int> r, p;

  DSU() {}

  DSU(int n) : r(n, 1), p(n) {
    for (int i = 0; i < n; ++i) p[i] = i;
  }

  int find(int a) {
    return a == p[a] ? a : p[a] = find(p[a]);
  }

  bool same_set(int a, int b) {
    return find(a) == find(b);
  }

  void link(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (r[a] < r[b]) swap(a, b);
    p[b] = a, r[a] += r[b];
  }
};

int n, m, sz, pa[500000], lv[500000], p2[1000001];
vector<int> adj[500000], radj[500000];
ll dp[500000][3];
bool vis[500000];
vector<pii> back;
DSU dsu;

void dfs(int v, int p, int l) {
  pa[v] = p, lv[v] = l;
  for (int u : adj[v]) {
    if (lv[u] < 0) dfs(u, v, l + 1);
    else if (u != p && lv[v] > lv[u]) back.push_back({v, u}), ++sz;
  }
}

void dfs2(int v, int p) {
  int c = 0;
  for (int u : radj[v]) if (u != p) ++c, dfs2(u, v);
  if (c == 0) {
    dp[v][0] = dp[v][1] = p2[dsu.r[v]] - 1, dp[v][2] = 1;
    return;
  }
  dp[v][2] = 1;
  for (int u : radj[v]) if (u != p) dp[v][2] = dp[v][2] * dp[u][2] % MOD;
  dp[v][2] = dp[v][2] * p2[c] % MOD;
  dp[v][0] = 1;
  for (int u : radj[v]) {
    if (u == p) continue;
    ll mult = (dp[u][0] + dp[u][2] * 2) % MOD;
    dp[v][0] = dp[v][0] * mult % MOD;
  }
  dp[v][0] = p2[dsu.r[v]] * dp[v][0] % MOD;
  dp[v][0] -= dp[v][2];
  if (dp[v][0] < 0) dp[v][0] += MOD;
  dp[v][1] = dp[v][0];
  ll empty = dp[v][2] * INV2 % MOD;
  for (int u : radj[v]) {
    if (u == p) continue;
    empty = empty * inv(dp[u][2]) % MOD;
    dp[v][1] +=  empty * dp[u][1] * 2 % MOD - empty * dp[u][0] % MOD;
    if (dp[v][1] < 0) dp[v][1] += MOD;
    else if (dp[v][1] >= MOD) dp[v][1] -= MOD;
    empty = empty * dp[u][2] % MOD;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  p2[0] = 1;
  for (int i = 1; i < 1000001; ++i) {
    p2[i] = p2[i - 1] * 2;
    if (p2[i] >= MOD) p2[i] -= MOD;
  }
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  for (int i = 0; i < n; ++i) lv[i] = -1;
  dfs(0, 0, 0);
  dsu = DSU(n);
  for (pii p : back) {
    int a = p.first, b = p.second;
    while (a != b && !vis[a]) {
      vis[a] = true;
      dsu.link(a, pa[a]);
      a = pa[a];
      ++sz;
    }
  }
  for (int v = 0; v < n; ++v) {
    for (int u : adj[v]) {
      int a = dsu.find(v), b = dsu.find(u);
      if (a == b) continue;
      radj[a].push_back(b);
    }
  }
  dfs2(dsu.find(0), 0);
  cout << dp[dsu.find(0)][1] * p2[sz] % MOD << '\n';
  return 0;
}