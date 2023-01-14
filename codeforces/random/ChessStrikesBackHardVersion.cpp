#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

template<typename T>
struct segment_tree {

  int n;
  vector<T> segtree;
  function<T(const T&,const T&)> join;
  T base = T();

  segment_tree() {}
  
  segment_tree(int n, function<T(const T&, const T&)> join, T base = T()) : n(n), join(join), base(base) {
    segtree.resize(n << 1, base);
  }

  void build() {
    for (int i = n - 1; i > 0; --i) segtree[i] = join(segtree[(i << 1)], segtree[(i << 1) | 1]);
  }

  segment_tree(vector<T> seq, function<T(const T&, const T&)> join, T base = T()) : n(seq.size()), join(join), base(base) {
    segtree.resize(n << 1, base);
    for (int i = 0; i < n; ++i) segtree[i + n] = seq[i];
    build();
  }

  void upd(int pos, T val) {
    for (segtree[pos += n] = val; pos > 1; pos >>= 1) segtree[pos >> 1] = join(segtree[pos], segtree[pos ^ 1]);
  }

  T qry(int l, int r) {
    T ans = base;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = join(ans, segtree[l++]);
      if (r & 1) ans = join(ans, segtree[--r]);
    }
    return ans;
  }
};

struct special_rmq_save {

  int p, ov;

  special_rmq_save() {}

  special_rmq_save(int p, int ov) : p(p), ov(ov) {}
};

struct special_rmq_with_rollbacks {

  int n;

  stack<special_rmq_save> chg_min;
  stack<special_rmq_save> chg_max;
  int szN;

  segment_tree<int> tmin, tmax;

  special_rmq_with_rollbacks() {}

  special_rmq_with_rollbacks(int n, int m) : n(n), szN(INT_MAX) {
    tmin = segment_tree<int>(n, [&](int x, int y) {return min(x, y);}, INT_MAX);
    tmax = segment_tree<int>(n, [&](int x, int y) {return max(x, y);}, -1);
  }

  void add(int x, int y) {
    --x, --y;
    x ^= 1, y ^= 1;
    chg_min.push(special_rmq_save(x / 2, tmin.segtree[x / 2 + n]));
    chg_max.push(special_rmq_save(x / 2, tmax.segtree[x / 2 + n]));
    if (x & 1) {
      if (chg_min.top().ov > y / 2) tmin.upd(x / 2, y / 2);
      if (tmax.qry(x / 2, n) >= y / 2 && szN == INT_MAX) szN = chg_min.size();
    } else {
      if (chg_max.top().ov < y / 2) tmax.upd(x / 2, y / 2);
      if (tmin.qry(0, x / 2 + 1) <= y / 2 && szN == INT_MAX) szN = chg_min.size();
    }
  }

  void pop() {
    if (chg_min.size() == szN) szN = INT_MAX;
    special_rmq_save cmn = chg_min.top(); chg_min.pop();
    special_rmq_save cmx = chg_max.top(); chg_max.pop();
    tmin.upd(cmn.p, cmn.ov), tmax.upd(cmx.p, cmx.ov);
  }

  bool works() {
    return szN == INT_MAX;
  }
};

vector<bool> ans;

struct custom_dynacon {

  special_rmq_with_rollbacks info;

  vector<vector<pii>> at;

  custom_dynacon() {}

  custom_dynacon(int n, int m, int q) : info(n, m), at(q << 2) {}

  void add(pii p, int l, int r, int v, int tl, int tr) {
    if (l > r) return;
    if (l == tl && r == tr) {
      at[v].push_back(p);
      return;
    }
    int m = (tl + tr) / 2;
    add(p, l, min(m, r), 2 * v, tl, m);
    add(p, max(m + 1, l), r, 2 * v + 1, m + 1, tr);
  }

  void dfs(int v, int tl, int tr) {
    for (pii p : at[v]) info.add(p.first, p.second);
    if (tl == tr) {
      ans.push_back(info.works());
      for (pii p : at[v]) info.pop();
      return;
    }
    int m = (tl + tr) / 2;
    dfs(2 * v, tl, m);
    dfs(2 * v + 1, m + 1, tr);
    for (pii p : at[v]) info.pop();
  }
};

int main() {
  int n, m, q; cin >> n >> m >> q;
  custom_dynacon dynacon(n, m, q);
  ans.reserve(q);
  set<pair<pii, int>> active;
  for (int i = 0; i < q; ++i) {
    int x, y; cin >> x >> y;
    auto it = active.lower_bound({{x, y}, 0});
    if (it == active.end() || it->first.first != x || it->first.second != y) active.insert({{x, y}, i});
    else dynacon.add(it->first, it->second, i - 1, 1, 0, q - 1), active.erase(it);
  }
  for (auto p : active) dynacon.add(p.first, p.second, q - 1, 1, 0, q - 1);
  dynacon.dfs(1, 0, q - 1);
  for (bool b : ans) cout << (b ? "YES\n" : "NO\n");
}