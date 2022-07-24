#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline void solve() {
  ll n, m, k; cin >> n >> m >> k;
  vector<ll> arr(k); for (int i = 0; i < k; ++i) cin >> arr[i];
  vector<ll> rows, cols;
  for (ll num : arr) rows.push_back(num / m), cols.push_back(num / n);
  sort(rows.begin(), rows.end()), sort(cols.begin(), cols.end());
  reverse(rows.begin(), rows.end()), reverse(cols.begin(), cols.end());
  ll n1 = n, n2 = m;
  bool g2 = false;
  for (ll num : rows) {
    if (n1 - num <= 0) {
      cout << "Yes\n";
      return;
    }
    if (num > 2) g2 = true;
    if (n1 - num > 1) n1 -= num;
    else if (n1 - num == 1 && g2) n1 = 2;
  }
  g2 = false;
  for (ll num : cols) {
    if (n2 - num <= 0) {
      cout << "Yes\n";
      return;
    }
    if (num > 2) g2 = true;
    if (n2 - num > 1) n2 -= num;
    else if (n2 - num == 1 && g2) n2 = 2;
  }
  cout << "No\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
