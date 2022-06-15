#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>

vector<ll> t;
vector<pll> lazy;

void push(int v, int l, int r) {
  int m = (l + r) / 2;
  int rl = m - l + 1, rr = r - m;
  if (lazy[v].first >= 0) {
    t[v << 1] = lazy[v].first * rl, t[(v << 1) + 1] = lazy[v].first * rr;
    lazy[v << 1].first = lazy[(v << 1) + 1].first = lazy[v].first;
    lazy[v << 1].second = lazy[(v << 1) + 1].second = 0;
  }
  t[v << 1] += lazy[v].second * rl, t[(v << 1) + 1] += lazy[v].second * rr;
  lazy[v << 1].second += lazy[v].second, lazy[(v << 1) + 1].second += lazy[v].second;
  lazy[v] = {-1, 0};
}

void u1(int v, int tl, int tr, int l, int r, ll add) {
  if (l > r) return;
  if (tl == l && tr == r) t[v] += (tr - tl + 1) * add, lazy[v].second += add;
  else {
    push(v, tl, tr);
    int m = (tl + tr) / 2;
    u1(v << 1, tl, m, l, min(m, r), add);
    u1((v << 1) + 1, m + 1, tr, max(m + 1, l), r, add);
    t[v] = t[v << 1] + t[(v << 1) + 1];
  }
}

void u2(int v, int tl, int tr, int l, int r, ll s) {
  if (l > r) return;
  if (tl != tr) push(v, tl, tr);
  if (tl == l && tr == r) t[v] = (tr - tl + 1) * s, lazy[v].first = s, lazy[v].second = 0;
  else {
    int m = (tl + tr) / 2;
    u2(v << 1, tl, m, l, min(m, r), s);
    u2((v << 1) + 1, m + 1, tr, max(m + 1, l), r, s);
    t[v] = t[v << 1] + t[(v << 1) + 1];
  }
}

ll query(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (tl == l && tr == r) return t[v];
  push(v, tl, tr);
  int m = (tl + tr) / 2;
  return query(v << 1, tl, m, l, min(m, r)) + query((v << 1) + 1, m + 1, tr, max(m + 1, l), r);
}

int main() {
  int n, q; cin >> n >> q; t.resize(4 * n), lazy.resize(4 * n); fill(lazy.begin(), lazy.end(), pll({-1, 0}));
  for (int i = 0; i < n; ++i) { int x; cin >> x; u1(1, 0, n - 1, i, i, x); }
  for (int i = 0; i < q; ++i) {
    int type, a, b; cin >> type >> a >> b; --a, --b;
    if (type == 1) { int x; cin >> x; u1(1, 0, n - 1, a, b, x); }
    else if (type == 2) { int x; cin >> x; u2(1, 0, n - 1, a, b, x); }
    else cout << query(1, 0, n - 1, a, b) << '\n';
  }
  return 0;
}
