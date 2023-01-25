#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
  int n, a, b, c, d; cin >> n >> a >> b >> c >> d;
  if (a * d > b * c) swap(a, c), swap(b, d);
  int ans = (n + c - 1) / c * d;
  for (int i = 1; i <= c; ++i) {
    int cost1 = i * b, cost2 = max(n - i * a + c - 1, 0LL) / c * d;
    ans = min(ans, cost1 + cost2);
  }
  cout << ans << '\n';
  return 0;
}
