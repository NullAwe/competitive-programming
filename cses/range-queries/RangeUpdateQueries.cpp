#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> t;
int n;

void modify(int l, int r, ll x) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) t[l++] += x;
    if (r & 1) t[--r] += x;
  }
}

ll query(int p) {
  ll ans;
  for (ans = t[p += n]; p > 1; p >>= 1) ans += t[p >> 1];
  return ans;
}

int main() {
  cin >> n;
  int q; cin >> q;
  t.resize(2 * n);
  for (int i = 0; i < n; ++i) {
    ll x; cin >> x;
    modify(i, i + 1, x);
  }
  for (int i = 0; i < q; ++i) {
    int type; cin >> type;
    if (type == 1) {
      int l, r, x; cin >> l >> r >> x; --l;
      modify(l, r, x);
    } else {
      int p; cin >> p; --p;
      cout << query(p) << '\n';
    }
  }
  return 0;
}

