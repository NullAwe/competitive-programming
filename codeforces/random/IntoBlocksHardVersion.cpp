#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse4,popcnt,abm,mmx,tune=native")
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int MAX_N = 200000;

pii rngs[MAX_N << 1];

struct LazySegtree {

  int n;
  pii t[MAX_N << 2];
  stack<pair<int, pii>> revisions;

  LazySegtree() {}

  LazySegtree(int n) : n(n) {
    for (int i = 0; i < (n << 2); ++i) t[i] = {-1, -1};
  }

  inline void addCheckpoint() {
    revisions.push({-1, {-1, -1}});
  }

  inline void push(int v, int tl, int tr) {
    if (t[v].first < 0 || tl == tr) return;
    int l = v << 1, r = (v << 1) ^ 1;
    if (t[l] != t[v]) revisions.push({l, t[l]}), t[l] = t[v];
    if (t[r] != t[v]) revisions.push({r, t[r]}), t[r] = t[v];
  }

  void upd(int v, int tl, int tr, int l, int r, int xl, int xr) {
    if (l > r) return;
    if (tl == l && tr == r) {
      if (t[v] != make_pair(xl, xr)) revisions.push({v, t[v]}), t[v] = {xl, xr};
      return;
    }
    push(v, tl, tr);
    int m = (tl + tr) >> 1;
    upd(v << 1, tl, m, l, min(m, r), xl, xr);
    upd((v << 1) ^ 1, m + 1, tr, max(m + 1, l), r, xl, xr);
  }

  inline void upd(int l, int r) {
    upd(1, 0, n - 1, l, r, l, r);
  }

  inline pii qry(int x) {
    int v = 1;
    int l = 0, r = n - 1;
    while (l != r) {
      push(v, l, r);
      int m = (l + r) >> 1;
      if (x <= m) v = v << 1, r = m;
      else v = (v << 1) ^ 1, l = m + 1;
    }
    return t[v];
  }

  inline void rollback() {
    while (revisions.size()) {
      pair<int, pii> p = revisions.top(); revisions.pop();
      if (p.first < 0) break;
      t[p.first] = p.second;
    }
  }
};

struct LazySumSegtree {

  int n;
  int t[MAX_N << 1];
  stack<pii> revisions;

  LazySumSegtree() {}

  LazySumSegtree(int n) : n(n) {
    memset(t, 0, sizeof(t));
  }

  inline void addCheckpoint() {
    revisions.push({-1, -1});
  }

  inline void upd0(int l, int r) {
    upd(l, -qry(l, r));
  }

  inline void upd(int p, int v) {
    if (!v) return;
    revisions.push({p + n, t[p + n]});
    for (t[p += n] += v; p > 1; p >>= 1) revisions.push({p >> 1, t[p >> 1]}), t[p >> 1] = t[p] + t[p ^ 1];
  }

  inline int qry(int l, int r) {
    int sum = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) sum += t[l++];
      if (r & 1) sum += t[--r];
    }
    return sum;
  }

  inline int qry() {
    return t[1];
  }

  inline void rollback() {
    while (revisions.size()) {
      pii p = revisions.top(); revisions.pop();
      if (p.first < 0) break;
      t[p.first] = p.second;
    }
  }
};

struct MaxSegtree {

  int n;
  vector<int> t;
  stack<pii> revisions;

  MaxSegtree() {}

  MaxSegtree(int n) : n(n), t(n << 1) {}

  inline void addCheckpoint() {
    revisions.push({-1, -1});
  }

  inline void upd(int p, int v) {
    if (t[p + n] != v) revisions.push({p + n, t[p + n]});
    for (t[p += n] = v; p > 1; p >>= 1) {
      if (t[p >> 1] != max(t[p], t[p ^ 1])) revisions.push({p >> 1, t[p >> 1]});
      t[p >> 1] = max(t[p], t[p ^ 1]);
    }
  }

  inline int qry(int l, int r) {
    int ans = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = max(ans, t[l++]);
      if (r & 1) ans = max(ans, t[--r]);
    }
    return ans;
  }

  inline int qry(int p) {
    return t[p + n];
  }

  inline void rollback() {
    while (revisions.size()) {
      pii p = revisions.top(); revisions.pop();
      if (p.first < 0) break;
      t[p.first] = p.second;
    }
  }
};

struct MagicWithRollback {

  int n;
  LazySegtree subsections;
  LazySumSegtree ans;
  MaxSegtree maxs;
  vector<int> begin;
  stack<pii> revisions;

  MagicWithRollback() {}

  MagicWithRollback(int n) : n(n), subsections(n), ans(n), maxs(n), begin(MAX_N, -1) {
    for (int i = 0; i < n; ++i) subsections.upd(i, i);
  }

  inline void addCheckpoint() {
    subsections.addCheckpoint();
    ans.addCheckpoint();
    maxs.addCheckpoint();
    revisions.push({-1, -1});
  }

  inline void addAt(int p, int v) {
    // individual stuff
    if (begin[v] < 0) {
      revisions.push({v, begin[v]});
      begin[v] = p;
    }
    int cur = maxs.qry(begin[v]) + 1;
    maxs.upd(begin[v], 0);
    maxs.upd(min(begin[v], p), cur);
    // group stuff
    pii orig = subsections.qry(p), nr = subsections.qry(begin[v]);
    int l = min(orig.first, nr.first), r = max(orig.second, nr.second);
    ans.upd0(l, r);
    ans.upd(l, maxs.qry(l, r));
    subsections.upd(l, r);
    // finalize
    if (begin[v] > p) revisions.push({v, begin[v]}), begin[v] = p;
  }

  inline void rollback() {
    subsections.rollback();
    ans.rollback();
    maxs.rollback();
    while (revisions.size()) {
      pii p = revisions.top(); revisions.pop();
      if (p.first < 0) break;
      begin[p.first] = p.second;
    }
  }

  int getAns() {
    return n - ans.qry();
  }
};

struct Dynacon {

  int n;
  vector<vector<pii>> t;
  MagicWithRollback mwr;

  Dynacon() {}

  Dynacon(int n, int q) : n(q), t(q << 2), mwr(n) {}

  void upd(int v, int tl, int tr, int l, int r, int p, int val) {
    if (l > r) return;
    if (tl == l && tr == r) {
      t[v].push_back({p, val});
      return;
    }
    int m = (tl + tr) >> 1;
    upd(v << 1, tl, m, l, min(m, r), p, val);
    upd((v << 1) ^ 1, m + 1, tr, max(m + 1, l), r, p, val);
  }

  inline void upd(int l, int r, int p, int v) {
    upd(1, 0, n - 1, l, r, p, v);
  }

  void dfs(int v, int tl, int tr) {
    mwr.addCheckpoint();
    for (pii p : t[v]) mwr.addAt(p.first, p.second);
    if (tl == tr) {
      cout << mwr.getAns() << '\n';
    } else {
      int m = (tl + tr) >> 1;
      dfs(v << 1, tl, m);
      dfs((v << 1) ^ 1, m + 1, tr);
    }
    mwr.rollback();
  }

  inline void dfs() {
    dfs(1, 0, n - 1);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; ++i) rngs[i + n] = {i, i};
  for (int i = n - 1; i > 0; --i) {
    rngs[i].first = min(rngs[i << 1].first, rngs[(i << 1) ^ 1].first);
    rngs[i].second = max(rngs[i << 1].second, rngs[(i << 1) ^ 1].second);
  }
  Dynacon dynacon(n, q + 1);
  vector<pii> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i].first;
  for (int i = 0; i < n; ++i) --arr[i].first;
  for (int t = 1; t <= q; ++t) {
    int p, x; cin >> p >> x; --p, --x;
    if (arr[p].first == x) continue;
    dynacon.upd(arr[p].second, t - 1, p, arr[p].first);
    arr[p] = {x, t};
  }
  for (int i = 0; i < n; ++i) dynacon.upd(arr[i].second, q, i, arr[i].first);
  dynacon.dfs();
  return 0;
}