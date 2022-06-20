#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> order, parent;

void dfs(int v, int p) {
  parent[v] = p;
  for (int u : adj[v]) if (u != p) dfs(u, v);
  if (v) order.push_back(v);
}

int main() {
  int n; cin >> n;
  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  parent.resize(n); dfs(0, 0);
  vector<int> size(n, 1);
  for (int v : order) size[parent[v]] += size[v];
  for (int v = 0; v < n; ++v) {
    int m = size[0] - size[v];
    for (int u : adj[v]) if (u != parent[v]) m = max(m, size[u]);
    if (m <= n / 2) {
      cout << v + 1 << '\n';
      return 0;
    }
  }
  return 0;
}

