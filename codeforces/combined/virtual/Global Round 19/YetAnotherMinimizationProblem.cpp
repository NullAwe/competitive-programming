#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll sq(ll x) { return x * x; }

void solve() {
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  vector<vector<bool>> possible(n + 1, vector<bool>(100 * n + 1));
  possible[0][0] = true;
  for (int i = 0; i < n; ++i) for (int j = 0; j <= 100 * n; ++j)
    if (possible[i][j]) possible[i + 1][j + a[i]] = possible[i + 1][j + b[i]] = true;
  int total = 0; for (int i = 0; i < n; ++i) total += a[i] + b[i];
  ll ans = LLONG_MAX;
  for (int i = 0; i <= 100 * n; ++i) if (possible[n][i]) ans = min(ans, sq(i) + sq(total - i));
  for (int i = 0; i < n; ++i) ans += (n - 2) * (sq(a[i]) + sq(b[i]));
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

