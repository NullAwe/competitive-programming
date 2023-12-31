#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>

struct Info {

  int c[3];

  Info() {
    c[0] = c[1] = c[2] = 0;
  }

  Info(int x, int y, int z) {
    c[0] = x, c[1] = y, c[2] = z;
  }
};

struct Info2 {
  int a, b, c, d;
  bool operator <(const Info2& rhs) const {
    return a < rhs.a || (a == rhs.a && d < rhs.d);
  }
};

struct Segtree {

  int n, lz[4000000];
  Info t[4000000];

  Segtree() {}

  Segtree(int n) : n(n) {}

  void build(int v, int tl, int tr) {
    t[v].c[0] = tr - tl + 1;
    if (tl == tr) return;
    int m = (tl + tr) / 2;
    build(2 * v, tl, m);
    build(2 * v + 1, m + 1, tr);
  }

  inline void combine(Info& into, const Info& l, const Info& r) {
    for (int i = 0; i < 3; ++i) into.c[i] = l.c[i] + r.c[i];
  }

  inline void push(int v, int l, int r) {
    if (l == r || lz[v] == 0) return;
    if (lz[v] > 0) {
      for (int i = 2; i >= lz[v]; --i) {
        t[2 * v].c[i] = t[2 * v].c[i - lz[v]];
        t[2 * v + 1].c[i] = t[2 * v + 1].c[i - lz[v]];
      }
      for (int i = 0; i < lz[v]; ++i) t[2 * v].c[i] = t[2 * v + 1].c[i] = 0;
    } else {
      for (int i = 0; i <= 2 + lz[v]; ++i) {
        t[2 * v].c[i] = t[2 * v].c[i - lz[v]];
        t[2 * v + 1].c[i] = t[2 * v + 1].c[i - lz[v]];
      }
      for (int i = 3 + lz[v]; i < 3; ++i) t[2 * v].c[i] = t[2 * v + 1].c[i] = 0;
    }
    lz[2 * v] += lz[v], lz[2 * v + 1] += lz[v];
    lz[v] = 0;
  }

  void upd(int v, int tl, int tr, int l, int r, int diff) {
    if (l > r) return;
    if (tl == l && tr == r) {
      lz[v] += diff;
      if (diff > 0) {
        for (int i = 2; i >= diff; --i) t[v].c[i] = t[v].c[i - diff];
        for (int i = 0; i < diff; ++i) t[v].c[i] = 0;
      } else {
        for (int i = 0; i <= 2 + diff; ++i) t[v].c[i] = t[v].c[i - diff];
        for (int i = 3 + diff; i < 3; ++i) t[v].c[i] = 0;
      }
      return;
    }
    push(v, tl, tr);
    int m = (tl + tr) / 2;
    upd(2 * v, tl, m, l, min(m, r), diff), upd(2 * v + 1, m + 1, tr, max(m + 1, l), r, diff);
    combine(t[v], t[2 * v], t[2 * v + 1]);
  }
};

struct RectTracker {

  int n;
  vector<Info2> chgs;
  Segtree st;

  RectTracker() {}

  RectTracker(int n) : n(n), st(n) {
    st.build(1, 0, n - 1);
  }

  inline void push(int i, int a, int b, int o) {
    chgs.push_back({a + o, i, b, 1});
    chgs.push_back({i + o + 1, i, b, -1});
  }

  inline ll area() {
    sort(chgs.begin(), chgs.end());
    int a = 0, i = 0;
    ll ans = 0;
    while (a < (int) chgs.size()) {
      while (a < (int) chgs.size() && chgs[a].a == i) {
        st.upd(1, 0, n - 1, chgs[a].b, chgs[a].c, chgs[a].d);
        ++a;
      }
      ans += st.t[1].c[2];
      ++i;
    }
    return ans;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<pii> mins(n), maxs(n);
  stack<pll> s; s.push({LLONG_MAX, -1});
  for (int i = 0; i < n; ++i) {
    while (s.top().first <= arr[i]) s.pop();
    maxs[i].first = s.top().second + 1;
    s.push({arr[i], i});
  }
  while (s.size()) s.pop(); s.push({LLONG_MAX, n});
  for (int i = n - 1; i >= 0; --i) {
    while (s.top().first < arr[i]) s.pop();
    maxs[i].second = s.top().second - 1;
    s.push({arr[i], i});
  }
  while (s.size()) s.pop(); s.push({LLONG_MIN, -1});
  for (int i = 0; i < n; ++i) {
    while (s.top().first >= arr[i]) s.pop();
    mins[i].first = s.top().second + 1;
    s.push({arr[i], i});
  }
  while (s.size()) s.pop(); s.push({LLONG_MIN, n});
  for (int i = n - 1; i >= 0; --i) {
    while (s.top().first > arr[i]) s.pop();
    mins[i].second = s.top().second - 1;
    s.push({arr[i], i});
  }
  ll ans = 0;
  RectTracker tracker(n);
  for (int i = 0; i < n; ++i) {
    int pc = __builtin_popcountll(arr[i]);
    tracker.push(i, mins[i].first, mins[i].second, pc * n);
    tracker.push(i, maxs[i].first, maxs[i].second, pc * n);
  }
  cout << tracker.area() << '\n';
  return 0;
}