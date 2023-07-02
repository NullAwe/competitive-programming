#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

int n;
vector<pii> edges;
vector<bool> ams;
vector<vector<pii>> adj;

struct MLST {

  vector<pii> t;
  vector<bool> lz;
  int nn;

  MLST() {}

  MLST(int nn) : nn(nn), t(4 * nn, {INT_MAX, INT_MIN}), lz(4 * nn) {}

  pii build(int v, int l, int r, vector<int>& arr) {
    if (l == r) return t[v] = {arr[l], arr[l]};
    int m = (l + r) / 2;
    pii _l = build(2 * v, l, m, arr), _r = build(2 * v + 1, m + 1, r, arr);
    return t[v] = {min(_l.first, _r.first), max(_l.second, _r.second)};
  }

  void build(vector<int>& arr) {
    build(1, 0, nn - 1, arr);
  }

  void push(int v, int l, int r) {
    if (!lz[v]) return;
    lz[v] = false;
    if (l == r) return;
    lz[2 * v] = !lz[2 * v], lz[2 * v + 1] = !lz[2 * v + 1];
    for (int i = 0; i < 2; ++i)
      t[2 * v + i] = {-t[2 * v + i].second, -t[2 * v + i].first};
  }

  pii flip(int v, int tl, int tr, int l, int r) {
    if (l > r) return t[v];
    if (tl == l && tr == r) {
      lz[v] = !lz[v];
      return t[v] = {-t[v].second, -t[v].first};
    }
    push(v, tl, tr);
    int m = (tl + tr) / 2;
    pii _l = flip(2 * v, tl, m, l, min(m, r));
    pii _r = flip(2 * v + 1, m + 1, tr, max(m + 1, l), r);
    return t[v] = {min(_l.first, _r.first), max(_l.second, _r.second)};
  }

  void flip(int l, int r) {
    flip(1, 0, nn - 1, l, r);
  }

  int qmx(int v, int tl, int tr, int l, int r) {
    if (l > r) return INT_MIN;
    if (tl == l && tr == r) return t[v].second;
    push(v, tl, tr);
    int m = (tl + tr) / 2;
    return max(qmx(2 * v, tl, m, l, min(m, r)), qmx(2 * v + 1, m + 1, tr, max(m + 1, l), r));
  }

  int qmx(int l, int r) {
    return qmx(1, 0, nn - 1, l, r);
  }
};

struct red_panda_tree {

  MLST minimax_lazy_segtree;
  vector<pii> rngs;
  vector<int> signs, depths, inds;
  int fv, nn;
  multiset<int> ones;

  red_panda_tree(int v) : fv(v), rngs(n), signs(n), depths(n) {}

  int rptdfs(int v, int p, int s, int l, int start) {
    signs[v] = s, depths[v] = l;
    int cur = start;
    for (pii u : adj[v]) {
      if (u.first == p) continue;
      cur += rptdfs(u.first, v, u.second ? -s : s, l + 1, cur);
    }
    if (cur == start) ++cur, inds.push_back(v);
    rngs[v] = {start, cur - 1};
    return cur - start;
  }

  void init() {
    rptdfs(fv, fv, 1, 0, 0);
    nn = inds.size();
    minimax_lazy_segtree = MLST(nn);
    vector<int> values;
    for (int idx : inds) values.push_back(signs[idx] * depths[idx]);
    minimax_lazy_segtree.build(values);
    for (int i = 0; i < n - 1; ++i)
      if (ams[i]) ones.insert(min(depths[edges[i].first], depths[edges[i].second]));
  }

  void flip(int idx) {
    int a = edges[idx].first, b = edges[idx].second;
    if (depths[a] < depths[b]) swap(a, b);
    minimax_lazy_segtree.flip(rngs[a].first, rngs[a].second);
    if (ams[idx]) ones.erase(ones.find(min(depths[edges[idx].first], depths[edges[idx].second])));
    else ones.insert(min(depths[edges[idx].first], depths[edges[idx].second]));
  }

  int mx() {
    int comp = ones.size() ? *--ones.end() : 0;
    return max(minimax_lazy_segtree.qmx(0, nn - 1), comp);
  }
};

pii dfs(int v, int p) {
  pii mx = {-1, v};
  for (pii u : adj[v]) if (u.first != p) mx = max(mx, dfs(u.first, v));
  return {mx.first + 1, mx.second};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b, c; cin >> a >> b >> c; --a, --b;
    edges.push_back({a, b}), ams.push_back(c), adj[a].push_back({b, c}); adj[b].push_back({a, c});
  }
  int u = dfs(0, 0).second;
  int v = dfs(u, u).second;
  red_panda_tree t1(u), t2(v); t1.init(), t2.init();
  int m; cin >> m;
  for (int i = 0; i < m; ++i) {
    int x; cin >> x; --x;
    t1.flip(x), t2.flip(x);
    ams[x] = !ams[x];
    cout << max(t1.mx(), t2.mx()) << '\n';
  }
  return 0;
}