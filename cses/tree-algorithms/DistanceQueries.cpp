#include <bits/stdc++.h>
using namespace std;

const int sz = 30;

vector<vector<int>> adj, up;
vector<int> levels, parents;

inline void dfs(int v, int p, int l) {
  levels[v] = l, parents[v] = p;
  for (int u : adj[v]) if (u != p) dfs(u, v, l + 1);
}

inline int query(int v, int u) {
  for (int i = 0; i < sz; ++i) if (u & (1 << i)) v = up[v][i];
  return v;
}

inline int lca(int a, int b) {
  if (levels[a] > levels[b]) a = query(a, levels[a] - levels[b]);
  else b = query(b, levels[b] - levels[a]);
  if (a == b) return a;
  for (int i = sz - 1; i >= 0; --i) if (up[a][i] != up[b][i]) a = up[a][i], b = up[b][i];
  return up[a][0];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  adj = vector<vector<int>>(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  levels = vector<int>(n); parents = vector<int>(n); dfs(0, 0, 0);
  up = vector<vector<int>>(n, vector<int>(sz));
  for (int i = 0; i < n; ++i) up[i][0] = parents[i];
  for (int j = 1; j < sz; ++j) for (int i = 0; i < n; ++i)
    up[i][j] = (up[i][j - 1] >= 0 ? up[up[i][j - 1]][j - 1] : -1);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    cout << levels[a] + levels[b] - 2 * levels[lca(a, b)] << '\n';
  }
  return 0;
}

