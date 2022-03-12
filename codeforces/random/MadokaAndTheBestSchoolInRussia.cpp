#include <bits/stdc++.h>
using namespace std;

int getFactors(int n) {
  int factors = 0;
  for (int i = 1; i * i <= n; ++i) if (n % i == 0) factors += i * i == n ? 1 : 2;
  return factors;
}

void solve() {
  int x, d, div = 0; cin >> x >> d;
  for (div = 0; x % d == 0; x /= d) ++div;
  if (div < 2) {
    cout << "NO\n";
    return;
  }
  int fx = getFactors(x), fd = getFactors(d);
  if (fx > 2 || (fd > 2 && div > 3)) cout << "YES\n";
  else if (fd > 2 && div == 3) {
    x *= d;
    for (int i = 1; i * i <= x; ++i) {
      if (x % i) continue;
      if (i % d > 0 && (x / i) % d > 0) {
        cout << "YES\n";
        return;
      }
    }
    cout << "NO\n";
  } else cout << "NO\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
