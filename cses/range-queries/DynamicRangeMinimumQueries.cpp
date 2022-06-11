#include <bits/stdc++.h>
using namespace std;

vector<int> t;
int n;

void modify(int p, int v) {
  for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
}

int query(int l, int r) {
  int ans = INT_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = min(ans, t[l++]);
    if (r & 1) ans = min(ans, t[--r]);
  }
  return ans;
}

int main() {
  cin >> n;
  int q; cin >> q;
  t.resize(2 * n);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    modify(i, x);
  }
  for (int i = 0; i < q; ++i) {
    int type, a, b; cin >> type >> a >> b;
    if (type == 1) modify(a - 1, b);
    else cout << query(a - 1, b) << '\n';
  }
  return 0;
}

