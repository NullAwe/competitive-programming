#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m, k; cin >> n >> m >> k;
  vector<vector<int>> reqs(k);
  vector<vector<vector<int>>> rowreq(n - 1);
  for (int i = 0; i < k; ++i) {
    int a, b, c, d; cin >> a >> b >> c >> d; --a, --b, --c, --d;
    if (a > c) swap(a, c), swap(b, d);
    reqs[i] = {a, b, c, d};
    rowreq[a].push_back(reqs[i]);
  }
  vector<vector<int>> adj(2 * (m - 1));
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < (int) rowreq[i].size(); ++j) {
      int i1 = 2 * min(rowreq[i][j][1], rowreq[i][j][3]) + (rowreq[i][j][1] > rowreq[i][j][3]);
      for (int l = j + 1; l < (int) rowreq[i].size(); ++l) {
        int i2 = 2 * min(rowreq[i][l][1], rowreq[i][l][3]) + (rowreq[i][l][1] > rowreq[i][l][3]);
        adj[i1].push_back(i2);
        adj[i2].push_back(i1);
      }
    }
  }
  vector<int> color(2 * (m - 1));
  set<int> left; for (int i = 0; i < 2 * (m - 1); ++i) left.insert(i);
  color[0] = 1;
  vector<bool> added(2 * (m - 1)); added[0] = true;
  queue<int> qdo; qdo.push(0);
  while (left.size() || qdo.size()) {
    while (left.size() && added[*left.begin()]) left.erase(left.begin());
    if (!left.size() && !qdo.size()) break;
    int v = left.size() ? *left.begin() : -1;
    if (qdo.size()) {
      v = qdo.front(); qdo.pop();
    } else {
      left.erase(v);
      if (color[v] > 0) continue;
      color[v] = 1;
    }
    added[v] = true;
    left.erase(v);
    if (!added[v ^ 1]) {
      color[v ^ 1] = 3 - color[v];
      qdo.push(v ^ 1);
    }
    int c = color[v];
    queue<int> q; q.push(v);
    while (q.size()) {
      v = q.front(); q.pop();
      for (int u : adj[v]) {
        if (color[u] > 0 && color[u] != c) {
          cout << "NO\n";
          return;
        }
        if (color[u]) continue;
        color[u] = c;
        added[u] = true;
        left.erase(u);
        q.push(u);
        qdo.push(u ^ 1);
        added[u ^ 1] = true;
        color[u ^ 1] = 3 - c;
        left.erase(u ^ 1);
      }
    }
  }
  cout << "YES\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
