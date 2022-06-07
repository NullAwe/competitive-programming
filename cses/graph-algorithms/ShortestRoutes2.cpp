#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll INF = 1e18;

int main() {
  int n, m, q; cin >> n >> m >> q;
  vector<vector<ll>> d(n, vector<ll>(n, INF));
  for (int i = 0; i < n; ++i) d[i][i] = 0;
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    d[a][b] = d[b][a] = min(d[a][b], (ll) w);
  }
  for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    cout << (d[a][b] == INF ? -1 : d[a][b]) << '\n';
  }
  return 0;
}
