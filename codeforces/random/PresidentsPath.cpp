#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
  int n, m; cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>(n));
  for (int i = 0; i < m; ++i) {
    int a, b, c; cin >> a >> b >> c;
    --a; --b;
    adj[a][b] = c;
    adj[b][a] = c;
  }
  vector<vector<int>> dist(n, vector<int>(n, INF));
  for (int i = 0; i < n; ++i) dist[i][i] = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (adj[i][j]) dist[i][j] = adj[i][j];
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
      dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
  vector<vector<int>> in(n, vector<int>(n));
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
    for (int k = 0; k < n; ++k)
      if (adj[k][j] > 0 && dist[i][k] + adj[k][j] == dist[i][j]) ++in[i][j];
  vector<vector<int>> ans(n, vector<int>(n));
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
    for (int k = 0; k < n; ++k) if (dist[i][k] + dist[k][j] == dist[i][j]) ans[i][j] += in[i][k];
  // Output:
  for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) cout << ans[i][j] << ' ';
  cout << endl;
  return 0;
}
