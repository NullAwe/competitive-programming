#include <bits/stdc++.h>
using namespace std;

// Finds answer using dynamic programming:
pair<int, int> dp(int node, vector<vector<int>>& adj) {
  vector<pair<int, int>> c;
  for (int next : adj[node]) c.push_back(dp(next, adj));
  if (c.size() == 0) return {0, 0};
  sort(c.begin(), c.end());
  int dist = 1;
  int start = 1, end = c.size(), ind = 0;
  if (node == 0) start = 0, end = c.size() - 1, ind = c.size() - 1;
  for (int i = start; i < end; ++i) dist = max(dist, max(c[i].first + 2, c[i].second));
  dist = max(dist, max(c[ind].first + 1, c[ind].second));
  return {c[0].first + 1, dist};
}

void solve() {
  int n; cin >> n;
  vector<vector<int>> adj(n), fixed(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b;
    --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  // Creates the tree (no edges from child to parent):
  vector<bool> vis(n);
  queue<int> todo;
  vis[0] = true;
  todo.push(0);
  while (todo.size()) {
    int node = todo.front(); todo.pop();
    for (int next : adj[node]) {
      if (vis[next]) continue;
      vis[next] = true;
      todo.push(next);
      fixed[node].push_back(next);
    }
  }
  // Output:
  cout << dp(0, fixed).second << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
