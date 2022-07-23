#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

ll p(ll x, ll y) {
  if (!y) return 1;
  ll b = p(x, y >> 1);
  b = b * b % MOD;
  if (y & 1) b *= x;
  return b % MOD;
}

ll inv(ll x) { return p(x, MOD - 2); }

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  vector<ll> sums(n + 1); for (int i = 0; i < n; ++i) sums[i + 1] = (sums[i] + arr[i]) % MOD;
  for (int i = 1; i <= n; ++i) {
    ll sum = 0;
    for (int j = n - 1; j >= 0; j -= i) {
      int l = max(j - i + 1, 0), mult = (n - 1 - j) / i;
      ll pf = sums[j + 1] - sums[l] + MOD;
      sum = (sum + pf * mult % MOD) % MOD;
    }
    cout << sum * inv(n) % MOD << ' ';
  }
  cout << '\n';
  return 0;
}

