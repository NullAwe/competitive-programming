#include <bits/stdc++.h>
using namespace std;

int getLower(int n, int bits) { return (n / (1 << bits)) * (1 << bits); }

int getHigher(int n, int bits) { return (n / (1 << bits) + 1) * (1 << bits); }

int c1(int a, int b) { return (b - a + 1) / 2; }

int c2(int a, int b, int bits) {
  if (a > b) return 0;
  if (a / (1 << bits) == b / (1 << bits)) {
    if (b % (1 << (bits + 1)) < (1 << bits)) return 0;
    return b - a + 1;
  }
  if (b % (1 << (bits + 1)) >= (1 << bits))
    return b - (getLower(b, bits + 1) + (1 << bits)) + 1;
  return getHigher(a, bits + 1) - a;
}

int c3(int a, int b, int bits) {
  return c2(a, getHigher(a, bits + 1) - 1, bits) +
    c1(getHigher(a, bits + 1), getLower(b, bits + 1) - 1) +
        c2(getLower(b, bits + 1), b, bits);
}

int getNum(int a, int b, int bit) {
  if ((a % (1 << (bit + 1)) == 0) &&
      (b % (1 << (bit + 1)) == (1 << (bit + 1)) - 1)) return c1(a, b);
  if (a / (1 << (bit + 1)) == b / (1 << (bit + 1))) return c2(a, b, bit);
  return c3(a, b, bit);
}

void solve() {
  int l, r; cin >> l >> r;
  int ans = INT_MAX;
  for (int i = 0; i < 30; ++i) ans = min(ans, r - l + 1 - getNum(l, r, i));
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
