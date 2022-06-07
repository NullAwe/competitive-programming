#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m; cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int> teams(n);
  for (int i = 0; i < n; ++i) {
    if (teams[i]) continue;
    teams[i] = 1;
    queue<int> q; q.push(i);
    while (q.size()) {
      int node = q.front(); q.pop();
      for (int next : adj[node]) {
        if (teams[next] == teams[node]) {
          cout << "IMPOSSIBLE\n";
          return 0;
        }
        if (teams[next]) continue;
        teams[next] = 3 - teams[node];
        q.push(next);
      }
    }
  }
  for (int team : teams) cout << team << ' ';
  cout << '\n';
  return 0;
}
