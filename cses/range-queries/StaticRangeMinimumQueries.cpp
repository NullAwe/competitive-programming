#include <bits/stdc++.h>
using namespace std;

void build(vector<int>& t, int n) {
  for (int i = n - 1; i > 0; --i) t[i] = min(t[i << 1], t[(i << 1) ^ 1]);
}

int query(vector<int>& t, int n, int l, int r) {
  int ans = INT_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = min(ans, t[l++]);
    if (r & 1) ans = min(ans, t[--r]);
  }
  return ans;
}

int main() {
  int n, q; cin >> n >> q;
  vector<int> t(2 * n);
  for (int i = n; i < 2 * n; ++i) cin >> t[i];
  build(t, n);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a;
    cout << query(t, n, a, b) << '\n';
  }
  return 0;
}

