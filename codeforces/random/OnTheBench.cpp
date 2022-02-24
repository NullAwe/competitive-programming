#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MOD = 1e9 + 7;

inline bool is(ll x) {
  ll lo = 0, hi = min(x + 1, MOD);
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    if (mid * mid == x) return true;
    if (mid * mid < x) lo = mid;
    else hi = mid;
  }
  return false;
}

int main() {
  int n; cin >> n;
  vector<ll> fact(n + 1); fact[0] = 1; for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
  ll nCr[n + 1][n + 1]; for (int i = 0; i <= n; ++i) nCr[i][0] = nCr[i][i] = 1;
  for (int i = 2; i <= n; ++i) for (int j = 1; j < i; ++j) nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]) % MOD;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int id = 0;
  vector<int> ids(n);
  for (int i = 0; i < n; ++i) {
    if (ids[i]) continue;
    ids[i] = ++id;
    for (int j = i + 1; j < n; ++j) if (is(arr[i] * arr[j])) ids[j] = id;
  }
  vector<int> sizes(id);
  for (int num : ids) ++sizes[num - 1];
  vector<vector<ll>> dp(id, vector<ll>(n));
  dp[0][sizes[0] - 1] = fact[sizes[0]];
  ll sum = sizes[0];
  for (int i = 1; i < id; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        for (int add = 0; add < sizes[i]; ++add) {
          int remove = j + add - k;
          if (remove < 0 || remove > j || remove + add > sizes[i] || sum + 1 - j < sizes[i] - remove - add) continue;
          ll perm = fact[sizes[i]], r = nCr[j][remove], o = nCr[sum + 1 - j][sizes[i] - remove - add], f = nCr[sizes[i] - 1][add];
          ll combined = ((perm * r % MOD) * o % MOD) * f % MOD;
          dp[i][k] = (dp[i][k] + dp[i - 1][j] * combined % MOD) % MOD;
        }
      }
    }
    sum = (sum + sizes[i]) % MOD;
  }
  cout << dp[id - 1][0] << endl;
  return 0;
}
