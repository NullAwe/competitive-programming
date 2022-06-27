#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<vector<int>> adj;
vector<int> order, p, d, ops;

int dfs(int v, int l) {
  for (int u : adj[v]) d[v] = max(d[v], dfs(u, l + 1) + 1);
  return d[v];
}

void dfs2(int v) {
  order.push_back(v);
  vector<pii> nexts(adj[v].size());
  for (int i = 0; i < adj[v].size(); ++i) nexts[i] = {d[adj[v][i]], adj[v][i]};
  sort(nexts.begin(), nexts.end());
  for (pii u : nexts) dfs2(u.second);
}

int main() {
  int n; cin >> n;
  adj.resize(n); p.resize(n), d = vector<int>(n, 1), ops.reserve(1e6);
  for (int i = 0; i < n - 1; ++i) {
    cin >> p[i + 1];
    adj[p[i + 1]].push_back(i + 1);
  }
  dfs(0, 0); dfs2(0);
  for (int v : order) cout << v << ' ';
  cout << '\n';
  vector<int> ops; ops.reserve(1e6);
  stack<int> ps; ps.push(0);
  for (int i = 0; i < n; ++i) {
    while (ps.top() != p[order[i]]) ops.push_back(order[i]), ps.pop();
    ps.push(order[i]);
  }
  cout << ops.size() << '\n';
  for (int v : ops) cout << v << ' ';
  cout << '\n';
  return 0;
}

