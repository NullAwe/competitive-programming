#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<ll> ans(n, 1); for (int i = 1; i < n; ++i) ans[i] = ans[i - 1] * 3;
  for (ll num : ans) {
    if (num > 1e9) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
  for (int num : ans) cout << num << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
