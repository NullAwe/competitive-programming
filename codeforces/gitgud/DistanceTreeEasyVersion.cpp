#include <bits/stdc++.h>
using namespace std;

int n, sz;
vector<vector<int>> adj;
vector<int> parent, levels;

void dfs(int v, int p, int l) {
  levels[v] = l, parent[v] = p;
  for (int u : adj[v]) if (u != p) dfs(u, v, l + 1);
}

void solve() {
  cin >> n;
  adj = vector<vector<int>>(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  parent = vector<int>(n), levels = vector<int>(n);
  dfs(0, 0, 0);
  int maxLevel = -1, lowest = -1;
  for (int i = 0; i < n; ++i) if (levels[i] > maxLevel) maxLevel = levels[i], lowest = i;
  queue<int> q;
  vector<int> dist(n);
  for (int w = 1; w <= n; ++w) {
    int lo = -1, hi = n;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (mid > maxLevel) hi = mid;
      else {
        int leaf = lowest;
        for (int i = 0; i < mid - w - 1; ++i) leaf = parent[leaf];
        q.push(leaf);
        for (int i = 0; i < n; ++i) dist[i] = -1;
        dist[leaf] = 0;
        while (q.size()) {
          int node = q.front(); q.pop();
          for (int next : adj[node]) {
            if (dist[next] >= 0) continue;
            q.push(next);
            dist[next] = dist[node] + 1;
          }
        }
        int maxDist = 0;
        for (int i = 0; i < n; ++i) if (levels[i] >= mid && dist[i] > maxDist) maxDist = dist[i];
        if (maxDist + w >= mid) lo = mid;
        else hi = mid;
      }
    }
    cout << lo << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
