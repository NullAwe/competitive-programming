#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

inline ll p(ll x, ll y) {
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD, y >>= 1;
  }
  return ans;
}

inline ll inv(ll x) {
  return p(x, MOD - 2);
}

int main() {
  int n, k; cin >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  ll ans = 1;
  int spaces = 1;
  int l = 0, r = n - 1;
  while (l < r) {
    if (arr[l] + arr[r] < k) {
      if (spaces == 0) {
        cout << 0 << '\n';
        return 0;
      }
      ans = ans * spaces % MOD;
      ++l, --spaces;
    } else ans = ans * spaces % MOD, --r, ++spaces;
  }
  if (arr[l] * 2 < k) {
    if (spaces == 0) {
      cout << 0 << '\n';
      return 0;
    }
  }
  ans = ans * spaces;
  vector<ll> f(n + 1); f[0] = 1;
  for (int i = 1; i <= n; ++i) f[i] = f[i - 1] * i % MOD;
  int last = -1, count = 0;
  for (int num : arr) {
    if (num == last) ++count;
    else {
      ans = ans * inv(f[count]) % MOD;
      last = num, count = 1;
    }
  }
  ans = ans * inv(f[count]) % MOD;
  cout << ans << '\n';
  return 0;
}
