#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

int n, m;
vector<vector<int>> adj;

vector<vector<int>> p(int k) {
  if (k == 1) return adj;
  vector<vector<int>> b = p(k >> 1);
  vector<vector<int>> bs(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int l = 0; l < n; ++l) {
        bs[i][l] = (bs[i][l] + (int) ((ll) b[i][j] * b[j][l] % MOD)) % MOD;
      }
    }
  }
  if (k & 1) {
    vector<vector<int>> fin(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int l = 0; l < n; ++l) {
          fin[i][l] = (fin[i][l] + (int) ((ll) bs[i][j] * adj[j][l] % MOD)) % MOD;
        }
      }
    }
    return fin;
  }
  return bs;
}

int main() {
  int k; cin >> n >> m >> k;
  adj = vector<vector<int>>(n, vector<int>(n));
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    ++adj[a][b];
  }
  cout << p(k)[0][n - 1] << '\n';
  return 0;
}

