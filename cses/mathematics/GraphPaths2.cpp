#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

int n, m;
vector<vector<ll>> adj;

vector<vector<ll>> p(int k) {
  if (k == 1) return adj;
  vector<vector<ll>> b = p(k >> 1);
  vector<vector<ll>> bs(n, vector<ll>(n, LLONG_MAX));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int l = 0; l < n; ++l) {
        if (b[i][j] == LLONG_MAX || b[j][l] == LLONG_MAX) continue;
        bs[i][l] = min(bs[i][l], b[i][j] + b[j][l]);
      }
    }
  }
  if (k & 1) {
    vector<vector<ll>> fin(n, vector<ll>(n, LLONG_MAX));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int l = 0; l < n; ++l) {
          if (bs[i][j] == LLONG_MAX || adj[j][l] == LLONG_MAX) continue;
          fin[i][l] = min(fin[i][l], bs[i][j] + adj[j][l]);
        }
      }
    }
    return fin;
  }
  return bs;
}

int main() {
  int k; cin >> n >> m >> k;
  adj = vector<vector<ll>>(n, vector<ll>(n, LLONG_MAX));
  for (int i = 0; i < m; ++i) {
    int a, b, c; cin >> a >> b >> c; --a, --b;
    adj[a][b] = min(adj[a][b], (ll) c);
  }
  ll ans = p(k)[0][n - 1]; if (ans == LLONG_MAX) ans = -1;
  cout << ans << '\n';
  return 0;
}

