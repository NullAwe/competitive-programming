#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> nCr(n + 1, vector<int>(n + 1));
  for (int i = 0; i <= n; ++i) nCr[i][0] = nCr[i][i] = 1;
  for (int i = 2; i <= n; ++i) for (int j = 1; j < i; ++j) nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]) % m;
  vector<ll> fact(n + 1); fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % m;
  ll ans = 0;
  if (n % 2 == 0) ans = fact[n - 2] * n % m;
  for (int l = 2; l <= (n + 1) / 2; ++l) {
    for (int len = l; len <= (n + 1) / 2; ++len) {
      ll ways = nCr[len - 2][l - 2];
      ll other = (n % 2 == 0 ? len : len - 1);
      ll rem = fact[n - l - 1] * n % m;
      ans = (ans + ways * other % m * rem % m) % m;
    }
  }
  cout << ans << '\n';
}

int main() {
  solve();
  return 0;
}
