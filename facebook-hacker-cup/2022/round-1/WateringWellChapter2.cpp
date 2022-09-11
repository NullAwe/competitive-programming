#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

int main() {
  ifstream in("in.txt");
  ofstream out("out.txt");
  int t; in >> t;
  for (int i = 1; i <= t; ++i) {
    int n; in >> n;
    ll sx2 = 0, sx = 0, sy2 = 0, sy = 0;
    for (int j = 0; j < n; ++j) {
      ll x, y; in >> x >> y;
      sx2 = (sx2 + x * x) % MOD, sx = (sx + x) % MOD;
      sy2 = (sy2 + y * y) % MOD, sy = (sy + y) % MOD;
    }
    int q; in >> q;
    ll ans = 0;
    for (int j = 0; j < q; ++j) {
      ll x, y; in >> x >> y;
      ans = (ans + sx2 + sy2) % MOD;
      ans = (ans - 2 * (x * sx + y * sy)) % MOD;
      ans = (ans + MOD) % MOD;
      ans = (ans + (n * x % MOD) * x) % MOD;
      ans = (ans + (n * y % MOD) * y) % MOD;
    }
    out << "Case #" << i << ": " << ans << '\n';
  }
}
