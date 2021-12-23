#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, l, r; cin >> n >> l >> r;
  vector<int> socks(n); for (int i = 0; i < n; ++i) cin >> socks[i];
  if (r > l) {
    reverse(socks.begin(), socks.end());
    swap(l, r);
  }
  int pairs = n / 2;
  set<int> ls, rs;
  map<int, int> lm, rm;
  for (int i = 0; i < l; ++i) {
    ls.insert(socks[i]);
    ++lm[socks[i]];
  }
  for (int i = l; i < n; ++i) {
    rs.insert(socks[i]);
    ++rm[socks[i]];
  }
  set<int> rem;
  for (int num : ls) {
    if (rs.count(num)) {
      rem.insert(num);
      int m = min(lm[num], rm[num]);
      pairs -= m; lm[num] -= m; rm[num] -= m;
    }
  }
  for (int num : rem) {
    if (lm[num] == 0) ls.erase(num);
    if (rm[num] == 0) rs.erase(num);
  }
  int mk = 0;
  for (int num : ls) mk += lm[num] / 2;
  pairs -= min(mk, (l - r) / 2);
  // Output:
  cout << (l - r) / 2 + pairs << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
