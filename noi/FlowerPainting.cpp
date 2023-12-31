#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

string arr[1000];
int rt[1001][1001];
int dn[1001][1001];

void solve() {
  int n, m, c, f, ca = 0, fa = 0; cin >> n >> m >> c >> f;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) rt[i][m] = dn[i][m] = 0;
  for (int i = 0; i < m; ++i) rt[n][i] = dn[n][i] = 0;
  for (int i = n - 1; i >= 0; --i) for (int j = m - 1; j >= 0; --j) {
    if (arr[i][j] == '0') rt[i][j] = rt[i][j + 1] + 1, dn[i][j] = dn[i + 1][j] + 1;
    else rt[i][j] = dn[i][j] = 0;
  }
  for (int j = 0; j < m; ++j) {
    bool reset = true;
    int s1 = 0, s2 = 0;
    for (int i = 0; i < n; ++i) {
      if (arr[i][j] == '1') {
        reset = true;
        continue;
      }
      if (i > n - 3) break;
      if (arr[i + 1][j] == '1' || arr[i + 2][j] == '1') continue;
      if (reset) {
        for (int k = i + 2; k < n; ++k) {
          if (arr[k][j] == '1') break;
          s1 += rt[k][j] - 1;
          if (s1 >= MOD) s1 -= MOD;
          s2 += (rt[k][j] - 1) * (dn[k][j] - 1) % MOD;
          if (s2 >= MOD) s2 -= MOD;
        }
      }
      ca += s1 * (rt[i][j] - 1) % MOD;
      if (ca >= MOD) ca -= MOD;
      fa += (ll) s2 * (rt[i][j] - 1) % MOD;
      if (fa >= MOD) fa -= MOD;
      s1 -= rt[i + 2][j] - 1;
      if (s1 < 0) s1 += MOD;
      s2 -= (rt[i + 2][j] - 1) * (dn[i + 2][j] - 1) % MOD;
      if (s2 < 0) s2 += MOD;
      reset = false;
    }
  }
  cout << ca * c << ' ' << fa * f << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t, id; cin >> t >> id;
  while (t--) solve();
  return 0;
}