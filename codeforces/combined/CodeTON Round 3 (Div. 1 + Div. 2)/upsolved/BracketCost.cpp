#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> t, ts, lazy, lazy2;

inline void m(int n, int p, int d, vector<ll>& rt, int mult) {
  for (rt[p += n] += d * mult; p > 1; p >>= 1) rt[p >> 1] = rt[p] + rt[p ^ 1];
}

inline ll q(int n, int l, int r, vector<ll>& rt) {
  ll ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += rt[l++];
    if (r & 1) ans += rt[--r];
  }
  return ans;
}

inline void push(int v, int tl, int tr) {
  if (tl != tr) {
    int l = 2 * v, r = 2 * v + 1, m = (tl + tr) / 2;
    if (lazy2[v] != LLONG_MAX) {
      lazy2[l] = lazy2[r] = lazy2[v], t[l] = lazy2[l] * (m - tl + 1), t[r] = lazy2[r] * (tr - m);
      lazy[l] = lazy[r] = 0;
    }
    lazy[l] += lazy[v], lazy[r] += lazy[v], t[l] += lazy[v] * (m - tl + 1), t[r] += lazy[v] * (tr - m);
  }
  lazy2[v] = LLONG_MAX, lazy[v] = 0;
}

inline void m2(int v, int tl, int tr, int l, int r, int d) {
  if (l > r) return;
  push(v, tl, tr);
  if (tl == l && tr == r) {
    lazy[v] += d, t[v] += d * (tr - tl + 1);
  }
  else {
    int m = (tl + tr) / 2;
    m2(2 * v, tl, m, l, min(m, r), d), m2(2 * v + 1, m + 1, tr, max(l, m + 1), r, d);
    t[v] = t[2 * v] + t[2 * v + 1];
  }
}

inline void m3(int v, int tl, int tr, int l, int r, int val) {
  if (l > r) return;
  push(v, tl, tr);
  if (tl == l && tr == r) {
    lazy2[v] = val, t[v] = val * (tr - tl + 1);
  }
  else {
    int m = (tl + tr) / 2;
    m3(2 * v, tl, m, l, min(m, r), val), m3(2 * v + 1, m + 1, tr, max(l, m + 1), r, val);
    t[v] = t[2 * v] + t[2 * v + 1];
  }
}

inline ll q2(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  push(v, tl, tr);
  if (tl == l && tr == r) {
    return t[v];
  }
  int m = (tl + tr) / 2;
  return q2(2 * v, tl, m, l, min(m, r)) + q2(2 * v + 1, m + 1, tr, max(l, m + 1), r);
}

inline ll qs(int v, int tl, int tr, int p) {
  while (tl != tr) {
    push(v, tl, tr);
    int m = (tl + tr) / 2;
    if (m >= p) v = 2 * v, tr = m;
    else v = 2 * v + 1, tl = m + 1;
  }
  push(v, tl, tr);
  return t[v];
}

inline void solve(int tc) {
  int n; cin >> n;
  string str; cin >> str;
  t.clear(), ts.clear();
  t.resize(4 * n + 2), ts.resize(4 * n + 2);
  int val = 0;
  m(2 * n + 1, n, 1, t, 1), m(2 * n + 1, n, 1, ts, 0);
  for (int i = 0; i < n; ++i) {
    val += (str[i] == '(' ? 1 : -1);
    m(2 * n + 1, val + n, 1, t, 1), m(2 * n + 1, val + n, 1, ts, val);
  }
  ll ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    m(2 * n + 1, val + n, -1, t, 1), m(2 * n + 1, val + n, -1, ts, val);
    ans += q(2 * n + 1, 0, val + n, t) * val - q(2 * n + 1, 0, val + n, ts);
    val -= (str[i] == '(' ? 1 : -1);
  }
  t.clear(), ts.clear(), lazy.clear(), lazy2.clear();
  t.resize(4 * n), ts.resize(4 * n), lazy.resize(4 * n), lazy2.resize(4 * n);
  for (int i = 0; i < 4 * n; ++i) lazy2[i] = LLONG_MAX;
  for (int i = 0; i < n; ++i) val += (str[i] == '(' ? 1 : -1);
  for (int i = n - 1; i >= 0; --i) {
    int chg = str[i] == '(' ? 1 : -1;
    m2(1, 0, n - 1, i, n - 1, chg);
    int lo = i, hi = n;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (qs(1, 0, n - 1, mid) >= chg) lo = mid;
      else hi = mid;
    }
    m3(1, 0, n - 1, i, lo, chg);
    lo = i - 1, hi = n;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (qs(1, 0, n - 1, mid) > 0) lo = mid;
      else hi = mid;
    }
    ans -= q2(1, 0, n - 1, hi, n - 1);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve(i);
  return 0;
}
