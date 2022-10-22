#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> odds, inds;
  for (int i = 0; i < n; ++i) if (arr[i] & 1) odds.push_back(arr[i]), inds.push_back(i);
  odds.push_back(MOD), inds.push_back(n);
  int o = odds.size();
  if (o == 0) {
    cout << 1 << '\n';
    return;
  }
  vector<int> p(o + 1, 1); p[0] = 0;
  for (int i = 0; i < n; ++i) {
    if (arr[i] & 1) continue;
    int oi = upper_bound(inds.begin(), inds.end(), i) - inds.begin();
    int l = oi - 1, r = oi;
    for (int j = l; j >= 0; --j) {
      if (abs(odds[j] - arr[i]) > 1) break;
      l = j;
    }
    if (l < 0 || abs(odds[l] - arr[i]) > 1) ++l;
    for (int j = r; j < o; ++j) {
      if (abs(odds[j] - arr[i]) > 1) break;
      r = j;
    }
    if (abs(odds[r] - arr[i]) > 1) --r;
    vector<int> dp(o, 0);
    for (int j = l; j <= r + 1; ++j) dp[j] = p[j + 1];
    for (int j = 0; j < o; ++j) p[j + 1] = (p[j] + dp[j]) % MOD;
  }
  cout << p[o] << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
