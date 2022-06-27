#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void solve(int t) {
  int n, m; cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
  }
  vector<int> in(n); for (int i = 0; i < n; ++i) for (int v : adj[i]) ++in[v];
  vector<int> order; order.reserve(n);
  queue<int> q;
  for (int i = 0; i < n; ++i) if (!in[i]) order.push_back(i), q.push(i);
  while (q.size()) {
    int v = q.front(); q.pop();
    for (int u : adj[v]) if (!--in[u]) order.push_back(u), q.push(u);
  }
  vector<int> sets(n);
  for (int v : order) {
    if (sets[v] == 3) continue;
    if (!sets[v]) sets[v] = 1;
    for (int u : adj[v]) if (sets[v] == 2 || !sets[u]) sets[u] = sets[v] % 3 + 1;
  }
  int count = 0; for (int num : sets) count += num == 3;
  cout << count << '\n';
  for (int i = 0; i < n; ++i) if (sets[i] == 3) cout << i + 1 << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve(i);
  return 0;
}

