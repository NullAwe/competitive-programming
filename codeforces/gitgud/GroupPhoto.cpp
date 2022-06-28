#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  if (n == 1) {
    cout << "1\n";
    return;
  }
  ll sum = 0, ans = 0, half = arr[0]; for (int num : arr) sum += num;
  for (int i = 1; i < n; ++i) {
    half += arr[i];
    if (half * 2 > sum) ++ans;
  }
  vector<ll> odd(n + 1), even(n + 1), norm(n + 1);
  for (int i = 0; i < n; ++i) {
    odd[i + 1] = odd[i], even[i + 1] = even[i], norm[i + 1] = norm[i] + arr[i];
    if (i & 1) odd[i + 1] += arr[i];
    else even[i + 1] += arr[i];
  }
  for (int i = 0; i < 4; ++i) {
    ll sc = (1 - (i & 1)) * arr[0] + (1 - ((i >> 1) & 1)) * arr[n - 1],
        sp = (i & 1) * arr[0] + ((i >> 1) & 1) * arr[n - 1];
    for (int c = 0; c < n - 1; ++c) {
      if (i & 1 && c == 0) {
        if (n == 2 && i < 3 && sp > sc) ++ans;
        sc += arr[c + 1];
        continue;
      }
      if (sp + norm[n - 1] - norm[c + 1] <= sc) break;
      int lo = 0, hi = (n - c - 2 - (1 - ((i >> 1) & 1))) / 2 + 1;
      while (lo < hi - 1) {
        int mid = (lo + hi) / 2 * 2;
        ll tc = sc, tp = sp + norm[n - 1] - norm[c + mid + 1];
        if ((c & 1) == 1) tc += odd[c + mid + 1] - odd[c + 1], tp += even[c + mid + 1] - even[c + 1];
        else tc += even[c + mid + 1] - even[c + 1], tp += odd[c + mid + 1] - odd[c + 1];
        if (tp > tc) lo = mid / 2;
        else hi = mid / 2;
      }
      ans += lo + 1, sc += arr[c + 1];
    }
  }
  cout << ans % MOD << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

