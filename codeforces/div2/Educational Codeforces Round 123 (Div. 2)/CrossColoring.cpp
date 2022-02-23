#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

void solve() {
  int n, m, k, q; cin >> n >> m >> k >> q;
  vector<pair<int, int>> ops(q);
  for (int i = 0; i < q; ++i) cin >> ops[i].first >> ops[i].second;
  reverse(ops.begin(), ops.end());
  set<int> x, y, xs, ys, see;
  for (int i = 0; i < q; ++i) {
    int a = ops[i].first, b = ops[i].second;
    if (xs.size() == n || ys.size() == m) continue;
    xs.insert(a); ys.insert(b);
    if (!x.count(a) || !y.count(b)) see.insert(i);
    x.insert(a); y.insert(b);
  }
  ll ans = 1;
  for (int i = 0; i < see.size(); ++i) ans = (ans * k) % MOD;
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
