#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

struct ST {

  int n;
  vector<int> t;

  ST() {}

  ST(int n) : n(n), t(4 * n) {}

  void inc(int v, int tl, int tr, int x) {
    ++t[v];
    if (tl == tr) return;
    int m = (tl + tr) / 2;
    if (x <= m) inc(2 * v, tl, m, x);
    else inc(2 * v + 1, m + 1, tr, x);    
  }

  void inc(int x) {
    inc(1, 0, n - 1, x);
  }

  int qry(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (tl == l && tr == r) return t[v];
    int m = (tl + tr) / 2;
    return qry(2 * v, tl, m, l, min(m, r)) + qry(2 * v + 1, m + 1, tr, max(m + 1, l), r);
  }

  int qry(int l, int r) {
    return qry(1, 0, n - 1, l, r);
  }
};

struct AHLD {

  int n, idat = 0;
  vector<int> order;
  vector<vector<int>> adj;
  vector<pii> rngs;
  ST st;

  AHLD() {}

  AHLD(int n, vector<int> ps) : n(n), adj(n), order(n), st(n), rngs(n) {
    for (int i = 1; i < n; ++i) adj[ps[i]].push_back(i);
  }

  void dfs(int v) {
    order[idat] = v;
    rngs[v].first = idat;
    ++idat;
    for (int u : adj[v]) dfs(u);
    rngs[v].second = idat - 1;
  }

  void init() {
    dfs(0);
    st.inc(0);
  }

  void inc_root(int x) {
    st.inc(rngs[x].first);
  }

  int get_size(int x) {
    return st.qry(rngs[x].first, rngs[x].second);
  }
};

struct BiHLD {

  int n, xs, cc, mxmx;
  vector<int> ps, lvl;
  vector<vector<int>> chs, rchs, up;
  AHLD hld;

  BiHLD() {}

  BiHLD(int n, vector<int> ps) : n(n), xs(1), ps(ps.begin(), ps.end()), chs(n), cc(0), rchs(n), lvl(n), up(20, vector<int>(n)), mxmx(0), hld(n, ps) {
    for (int i = 0; i < n; ++i) up[0][i] = ps[i];
    for (int i = 1; i < 20; ++i) {
      for (int j = 0; j < n; ++j) {
        up[i][j] = up[i - 1][up[i - 1][j]];
      }
    }
    hld.init();
    for (int i = 1; i < n; ++i) rchs[ps[i]].push_back(i);
  }

  void dfs(int root, int l) {
    lvl[root] = l;
    for (int u : rchs[root]) dfs(u, l + 1);
  }

  void init() {
    dfs(0, 0);
  }

  void inc_root(int x) {
    hld.inc_root(x);
  }

  int get_size(int x) {
    return hld.get_size(x);
  }

  int jmp(int a, int u) {
    for (int i = 0; i < 20; ++i) if (u & (1 << i)) a = up[i][a];
    return a;
  }

  bool is_anc(int a, int b) {
    if (lvl[a] >= lvl[b]) return false;
    b = jmp(b, lvl[b] - lvl[a]);
    return a == b;
  }

  int almost(int a, int b) {
    return jmp(a, lvl[a] - lvl[b] - 1);
  }

  void activate(int x) {
    ++xs;
    chs[ps[x]].push_back(x);
    inc_root(x);
    if (is_anc(cc, x)) mxmx = max(mxmx, get_size(almost(x, cc)));
    else mxmx = max(mxmx, xs - get_size(cc));
    if ((xs - get_size(cc)) * 2 > xs) cc = ps[cc], mxmx = xs / 2;
    else if (is_anc(cc, x) && get_size(almost(x, cc)) * 2 > xs) {
      cc = almost(x, cc), mxmx = xs / 2;
    }
  }
};

void solve() {
  int n; cin >> n;
  vector<int> ps(n), order; ps[0] = 0;
  for (int i = 1; i < n; ++i) {
    int x; cin >> x; --x;
    ps[i] = x;
    order.push_back(x);
  }
  BiHLD hld(n, ps);
  hld.init();
  vector<int> ans;
  for (int i = 0; i < n - 1; ++i) {
    hld.activate(i + 1);
    ans.push_back(max(i + 2 - 2 * hld.mxmx, i & 1));
  }
  for (int num : ans) cout << num << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}