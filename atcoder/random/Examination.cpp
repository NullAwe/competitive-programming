#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

struct lazy_segtree {
   
  int n;
  vector<int> t, lazy;

  lazy_segtree(int n) : n(n), t(4 * n), lazy(4 * n) {}

  inline void push(int v, int tl, int tr) {
    if (tl == tr || !lazy[v]) return;
    t[2 * v] += lazy[v], t[2 * v + 1] += lazy[v];
    lazy[2 * v] += lazy[v], lazy[2 * v + 1] += lazy[v];
    lazy[v] = 0;
  }

  void upd_delta(int v, int tl, int tr, int l, int r, int delta) {
    if (l > r) return;
    push(v, tl, tr);
    if (tl == l && tr == r) {
      t[v] += delta, lazy[v] = delta;
      return;
    }
    int m = (tl + tr) / 2;
    upd_delta(2 * v, tl, m, l, min(m, r), delta), upd_delta(2 * v + 1, m + 1, tr, max(m + 1, l), r, delta);
    t[v] = min(t[2 * v], t[2 * v + 1]);
  }

  void upd_delta(int l, int r, int delta) {
    upd_delta(1, 0, n - 1, l, r, delta);
  }

  int qry_full() {
    return t[1];
  }
};

int main() {
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
  vector<int> ca = a, cb = b;
  sort(ca.begin(), ca.end()), sort(cb.begin(), cb.end());
  for (int i = 0; i < n; ++i) {
    if (ca[i] < cb[i]) {
      cout << -1 << '\n';
      return 0;
    }
  }
  vector<pii> pa(n), pb(n);
  for (int i = 0; i < n; ++i) pa[i] = {a[i], i}, pb[i] = {b[i], i};
  sort(pa.begin(), pa.end()), sort(pb.begin(), pb.end());
  vector<int> ns(n);
  for (int i = 0; i < n; ++i) ns[pb[i].second] = i;
  lazy_segtree lazy(n); for (int i = 0; i < n; ++i) lazy.upd_delta(i, i, i + 1);
  int keep = n, to = 0;
  for (int i = 0; i < n; ++i) {
    int val = pa[i].first, ind = pa[i].second;
    while (to < n - 1 && pb[to + 1].first <= val) ++to;
    int atb = ns[ind];
    if (atb <= to) {
      lazy.upd_delta(atb, n - 1, -1);
      if (lazy.qry_full() < 0) {
        --keep;
        lazy.upd_delta(atb, n - 1, 1);
        lazy.upd_delta(to, n - 1, -1);
      }
    } else {
      --keep;
      lazy.upd_delta(to, n - 1, -1);
    }
  }
  cout << keep << '\n';
  return 0;
}