#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) --arr[i];
  vector<vector<int>> p(n, vector<int>(n + 1));
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) p[i][j + 1] = p[i][j] + (arr[j] < arr[i]);
  ll ans = 0;
  for (int i = 1; i < n; ++i) for (int j = i + 1; j < n - 1; ++j) ans += (ll) p[j][i] * (p[i][n] - p[i][j + 1]);
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}