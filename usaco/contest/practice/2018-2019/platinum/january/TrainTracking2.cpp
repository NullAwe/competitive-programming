#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;
const int MAX = 1e9;

int n, k;

ll p(ll x, ll y) {
  if (!y) return 1;
  ll b = p(x, y >> 1);
  b = b * b % MOD;
  if (y & 1) b *= x;
  return b % MOD;
}

ll g(vector<ll>& arr, int i) {
  return i < -2 ? 0 : (i < 0 ? 1 : arr[i]);
}

ll solve(ll x, ll y) {
  ll poly = 1, exp = 1; for (int i = 0; i < k; ++i) exp = exp * x % MOD;
  vector<ll> dp(y);
  for (int i = 0; i < y; ++i) {
    poly = (poly * x % MOD + g(dp, i - 1)) % MOD;
    poly = (poly - exp * g(dp, i - k - 1) % MOD + MOD) % MOD;
    dp[i] = poly;
  }
  return dp[y - 1];
}

int main() {
  ifstream in("tracking2.in");
  ofstream out("tracking2.out");
  in >> n >> k;
  vector<int> arr(n), track(n); for (int i = k - 1; i < n; ++i) in >> arr[i];
  multiset<int> s;
  for (int i = 0; i < n; ++i) {
    if (i + k - 1 < n) s.insert(arr[i + k - 1]);
    track[i] = *--s.end();
    if (s.find(arr[i]) != s.end()) s.erase(s.find(arr[i]));
  }
  for (int i = k; i < n; ++i) {
    if (arr[i] < arr[i - 1]) track[i] = 0;
    else if (arr[i] > arr[i - 1]) track[i - k] = 0;
  }
  ll ans = 1;
  for (int i = 0; i < n; ++i) {
    if (!track[i]) continue;
    int j;
    for (j = i; j < n && track[i] == track[j]; ++j);
    if (j - i < k) ans = ans * p(MAX - track[i] + 1, j - i) % MOD;
    else ans = ans * solve(MAX - track[i], j - i) % MOD;
    i = j - 1;
  }
  out << ans << '\n';
  return 0;
}
