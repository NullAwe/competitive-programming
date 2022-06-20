#include <bits/stdc++.h>
using namespace std;

const int sz = 30;

vector<vector<int>> adj, up;
vector<int> levels, parent, diff;

void dfs(int v, int p, int l) {
  levels[v] = l, parent[v] = p;
  for (int u : adj[v]) if (u != p) dfs(u, v, l + 1);
}

void dfs2(int v, int p) {
  for (int u : adj[v]) if (u != p) dfs2(u, v), diff[v] += diff[u];
}

int query(int a, int u) {
  for (int i = 0; i < sz; ++i) if (u & (1 << i)) a = up[a][i];
  return a;
}

int lca(int a, int b) {
  if (levels[a] < levels[b]) swap(a, b);
  a = query(a, levels[a] - levels[b]);
  if (a == b) return a;
  for (int i = sz - 1; i >= 0; --i) if (up[a][i] != up[b][i]) a = up[a][i], b = up[b][i];
  return up[a][0];
}

int main() {
  int n, m; cin >> n >> m;
  adj = vector<vector<int>>(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  levels = vector<int>(n), parent = vector<int>(n); dfs(0, 0, 0);
  up = vector<vector<int>>(n, vector<int>(30));
  for (int i = 0; i < n; ++i) up[i][0] = parent[i];
  for (int i = 1; i < sz; ++i) for (int j = 0; j < n; ++j) up[j][i] = up[up[j][i - 1]][i - 1];
  diff = vector<int>(n);
  vector<int> lcas(m);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    lcas[i] = lca(a, b);
    ++diff[a], ++diff[b], diff[lcas[i]] -= 2;
  }
  dfs2(0, 0);
  for (int p : lcas) ++diff[p];
  for (int num : diff) cout << num << ' ';
  cout << '\n';
  return 0;
}
