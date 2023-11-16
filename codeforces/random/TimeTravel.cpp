#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int main() {
  int n, t; cin >> n >> t;
  vector<set<pii>> adj(n);
  for (int i = 0; i < t; ++i) {
    int m; cin >> m;
    for (int j = 0; j < m; ++j) {
      int u, v; cin >> u >> v; --u; --v;
      adj[u].insert({v, i});
      adj[v].insert({u, i});
    }
  }
  vector<vector<int>> go(t);
  vector<bool> in(n); in[0] = true;
  for (pii p : adj[0]) {
    go[p.second].push_back(p.first);
    adj[p.first].erase({0, p.second});
  }
  adj[0].clear();
  int k; cin >> k;
  for (int i = 0; i < k; ++i) {
    int x; cin >> x; --x;
    vector<int> ng;
    for (int v : go[x]) {
      in[v] = true;
      for (pii p : adj[v]) {
        if (p.second == x) {
          ng.push_back(p.first);
          continue;
        }
        go[p.second].push_back(p.first);
        adj[p.first].erase({v, p.second});
      }
      adj[v].clear();
    }
    go[x] = ng;
    if (in[n - 1]) {
      cout << i + 1 << endl;
      return 0;
    }
  }
  cout << -1 << endl;
  return 0;
}