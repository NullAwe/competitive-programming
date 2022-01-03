#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  pair<int, int> a = {INT_MAX, 0}, b = {0, 0}, br = {0, 0};
  int cost = INT_MAX;
  for (int i = 0; i < n; ++i) {
    int l, r, c; cin >> l >> r >> c;
    if (l < a.first || (l == a.first && c < a.second)) a = {l, c};
    if (r > b.first || (r == b.first && c < b.second)) b = {r, c};
    if (l == br.first && r == br.second) {
      if (c < cost) {
        br = {l, r};
        cost = c;
      }
    } else if (l <= br.first && r >= br.second || i == 0) {
      br = {l, r};
      cost = c;
    }
    int sum = a.second + b.second;
    if (br.first == a.first && br.second == b.first) sum = min(sum, cost);
    // Output:
    cout << sum << endl;
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
