#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> vis;
vector<int> path;

int dfs(int v, int p) {
  if (vis[v]) return -1;
  vis[v] = true;
  for (int u : adj[v]) {
    if (u == p) continue;
    if (vis[u]) {
      path.push_back(v);
      return u;
    }
    int next = dfs(u, v);
    if (next < 0 && path.size()) return -1;
    if (next >= 0) {
      path.push_back(v);
      return v == next ? -1 : next;
    }
  }
  return -1;
}

int main() {
  int n, m; cin >> n >> m;
  adj = vector<vector<int>>(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vis = vector<bool>(n);
  for (int i = 0; i < n && !path.size(); ++i) dfs(i, i);
  if (!path.size()) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  cout << path.size() + 1 << '\n';
  cout << path.back() + 1;
  for (int num : path) cout << ' ' << num + 1;
  cout << '\n';
  return 0;
}
