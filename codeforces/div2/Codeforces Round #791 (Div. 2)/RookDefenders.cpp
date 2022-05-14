#include <bits/stdc++.h>
using namespace std;

void modify(vector<pair<int, int>>& t, int n, int p, int inc) {
  for (t[p += n].second += inc, t[p].first = t[p].second > 0; p > 1; p >>= 1) t[p >> 1].first = t[p].first + t[p ^ 1].first;
}

int query(vector<pair<int, int>>& t, int n, int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++].first;
    if (r & 1) ans += t[--r].first;
  }
  return ans;
}


void solve() {
  int n, q; cin >> n >> q;
  vector<pair<int, int>> tr(2 * n), tc(2 * n);
  for (int i = 0; i < q; ++i) {
    int t; cin >> t;
    if (t < 3) {
      int r, c; cin >> r >> c; --r; --c;
      modify(tr, n, r, (3 - 2 * t)), modify(tc, n, c, (3 - 2 * t));
    } else {
      int a, b, c, d; cin >> a >> b >> c >> d;
      cout << (query(tr, n, a - 1, c) == c - a + 1 || query(tc, n, b - 1, d) == d - b + 1 ? "Yes\n" : "No\n");
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  solve();
  return 0;
}
