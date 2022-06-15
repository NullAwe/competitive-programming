#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>

vector<ll> t;
vector<pll> lazy;

void push(int v, int l, int r) {
  int m = (l + r) / 2, rl = m - l + 1, rr = r - m;
  ll sl = rl * (lazy[v].first * 2 + (rl - 1) * lazy[v].second) / 2, sr = rr * ((lazy[v].first + rl * lazy[v].second) * 2 + (rr - 1) * lazy[v].second) / 2;
  t[v << 1] += sl, t[(v << 1) + 1] += sr;
  lazy[v << 1].first += lazy[v].first, lazy[(v << 1) + 1].first += lazy[v].first + rl * lazy[v].second;
  lazy[v << 1].second += lazy[v].second, lazy[(v << 1) + 1].second += lazy[v].second;
  lazy[v] = {0, 0};
}

void up(int v, int tl, int tr, int l, int r, ll add) {
  if (l > r) return;
  if (tl == l && tr == r) t[v] += (add * 2 + tr - tl) * (tr - tl + 1) / 2, lazy[v].first += add, ++lazy[v].second;
  else {
    push(v, tl, tr);
    int m = (tl + tr) / 2;
    up(v << 1, tl, m, l, min(m, r), add);
    up((v << 1) + 1, m + 1, tr, max(m + 1, l), r, add + max(m + 1 - l, 0));
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
  int n, q; cin >> n >> q; t.resize(4 * n), lazy.resize(4 * n); fill(lazy.begin(), lazy.end(), pll({0, 0}));
  for (int i = 0; i < n; ++i) { int x; cin >> x; up(1, 0, n - 1, i, i, x); }
  for (int i = 0; i < q; ++i) {
    int type, a, b; cin >> type >> a >> b; --a, --b;
    if (type == 1) up(1, 0, n - 1, a, b, 1);
    else cout << query(1, 0, n - 1, a, b) << '\n';
  }
  return 0;
}
