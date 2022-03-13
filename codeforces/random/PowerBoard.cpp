#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll GCD(ll a, ll b) {
  if (b == 0) return a;
  return GCD(b, a % b);
}

ll LCM(ll a, ll b) {
  return a * b / GCD(a, b);
}

int main() {
  ll n, m; cin >> n >> m;
  vector<int> board(n + 1); board[1] = 1;
  vector<vector<int>> ma(n + 1);
  for (int i = 2; i <= n; ++i) {
    if (board[i] > 0) continue;
    vector<int> arr;
    for (ll base = i; base <= n; base *= i) {
      board[base] = i;
      arr.push_back(base);
    }
    ma[i] = arr;
  }
  ll ans = (n - 1) * m + 1;
  for (int i = 2; i <= n; ++i) {
    vector<int> arr = ma[i];
    for (int j = 0; j < (1 << arr.size()); ++j) {
      if (__builtin_popcount(j) < 2) continue;
      int mult = __builtin_popcount(j) % 2 == 1 ? 1 : -1;
      ll _lcm = 1; for (int k = 0; k < arr.size(); ++k) if ((1 << k) & j) _lcm = LCM(_lcm, k + 1);
      int first; for (first = 0; first < arr.size(); ++first) if ((1 << first) & j) break;
      _lcm /= first + 1;
      ans += mult * (m / _lcm);
    }
  }
  cout << ans << '\n';
  return 0;
}
