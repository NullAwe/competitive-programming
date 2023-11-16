#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int> a, vector<int> b) {
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  int l = -1, r = n;
  while (l < r - 1) {
    int m = (l + r) / 2;
    bool ok = true;
    for (int i = 0; i < n - m; ++i) {
      if (a[i] >= b[i + m]) {
        ok = false;
        break;
      }
    }
    if (ok) r = m;
    else l = m;
  }
  return r;
}

void solve() {
  int n, m; cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n - 1; ++i) cin >> a[i];
  vector<int> b(n);
  for (int i = 0; i < n; ++i) cin >> b[i];
  a.back() = 1;
  int ans1 = solve(n, a, b);
  a.back() = m;
  int ans2 = solve(n, a, b);
  if (ans1 == ans2) {
    cout << (long long) ans1 * m << '\n';
    return;
  }
  int l = 1, r = m;
  while (l < r - 1) {
    int mid = (l + r) / 2;
    a.back() = mid;
    int ans = solve(n, a, b);
    if (ans == ans1) l = mid;
    else r = mid;
  }
  cout << (long long) ans1 * l + (long long) ans2 * (m - l) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}