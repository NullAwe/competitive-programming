#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n, m, p; cin >> n >> p;
  vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  cin >> m;
  vector<int> b(m); for (int i = 0; i < m; ++i) cin >> b[i];
  ll l = 0, r = 0, sl = 0, sr = 0;
  vector<ll> nums;
  while (l < n && r < m) {
    nums.push_back(a[l]), sl += a[l++];
    while (sl != sr) {
      if ((sl < sr && l >= n) || (sr < sl && r >= m)) {
        cout << "No\n";
        return;
      }
      if (sl < sr) nums.push_back(a[l]), sl += a[l++];
      else nums.push_back(b[r]), sr += b[r++];
    }
    sort(nums.begin(), nums.end());
    ll cur = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      while (cur < nums[i]) cur *= p;
      if (cur > nums[i]) {
        cout << "No\n";
        return;
      }
    }
    nums.clear(), sl = sr = 0;
  }
  if (l != n || r != m || sl != sr) {
    cout << "No\n";
    return;
  }
  cout << "Yes\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
