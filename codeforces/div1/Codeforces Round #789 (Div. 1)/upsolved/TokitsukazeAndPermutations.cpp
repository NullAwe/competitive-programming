#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) {
    if (arr[i] > i || (n - i <= k && arr[i] > 0)) {
      cout << 0 << '\n';
      return;
    }
  }
  for (int i = n - 1; i >= k; --i) arr[i] = arr[i - k];
  for (int i = 0; i < k; ++i) arr[i] = 0;
  ll ans = 1;
  for (int i = 0; i < n; ++i) {
    if (arr[i] == 0) ans *= min(i + 1, k + 1);
    else if (arr[i] < 0) ans *= i + 1;
    ans %= MOD;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
