#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  n = (1 << n) - 2;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int diff = 0;
  for (int i = 0; i < n; ++i) if (adj[i].size() != 3 && adj[i].size() != 1) ++diff;
  if (diff > 2) {
    cout << "0\n";
    return 0;
  }
  if (n == 2) {
    cout << "2\n1 2\n";
    return 0;
  }
  vector<int> leaves, nl;
  for (int i = 0; i < n; ++i) {
    if (adj[i].size() == 1) leaves.push_back(i);
    else nl.push_back(i);
  }
  vector<int> dists(n, -1); for (int leaf : leaves) dists[leaf] = 0;
  vector<int> ways(n); for (int leaf : leaves) ways[leaf] = 1;
  queue<int> q; for (int leaf : leaves) q.push(leaf);
  vector<int> order;
  while (q.size()) {
    int node = q.front(); q.pop();
    order.push_back(node);
    for (int next : adj[node]) {
      if (dists[next] >= 0) {
        if (dists[next] == dists[node] + 1) ways[next] += ways[node];
        continue;
      }
      dists[next] = dists[node] + 1;
      ways[next] = ways[node];
      q.push(next);
    }
  }
  vector<int> waymore(n);
  for (int node : order) for (int next : adj[node]) {
    if (dists[next] == dists[node]) waymore[node] += ways[next];
    if (dists[next] == dists[node] - 1) waymore[node] += waymore[next];
  }
  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    if (waymore[i] + ways[i] != leaves.size()) continue;
    int temp = ways[i];
    while ((temp & 1) == 0) temp >>= 1;
    if (temp == 1 || waymore[i] == 0) ans.push_back(i);
  }
  vector<int> missing;
  for (int node : ans) {
    int start = node;
    vector<bool> vis(n);
    while (true) {
      vis[node] = true;
      int after = -1;
      if (waymore[node] == 0) {
        int m = ways[node];
        for (int next : adj[node]) {
          if (vis[next]) continue;
          if (0 < ways[next] && ways[next] < m && dists[next] == dists[node] - 1) {
            m = ways[next];
            after = next;
          }
        }
      } else {
        for (int next : adj[node]) {
          if (vis[next]) continue;
          if (ways[next] == ways[node] && dists[next] == dists[node] - 1) {
            after = next;
            break;
          }
        }
      }
      if (after < 0) {
        bool works = true;
        for (int i : nl) {
          if (i == start || i == node) continue;
          if (adj[i].size() != 3) {
            works = false;
            break;
          }
        }
        if (!works) break;
        missing.push_back(node);
        break;
      }
      node = after;
    }
  }
  cout << missing.size() << '\n';
  for (int num : missing) cout << num + 1 << ' ';
  cout << '\n';
}