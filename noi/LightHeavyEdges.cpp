#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int MAX_N = 100000;
const int BUF_SZ = 1 << 15;

inline namespace Input {

  char buf[BUF_SZ];
  int pos, len;

  char next_char() {
    if (pos == len) {
      pos = 0, len = (int) fread(buf, 1, BUF_SZ, stdin);
      if (!len) return EOF;
	}
    return buf[pos++];
  }

  int read_int() {
    int x, sgn = 1;
    char ch;
    while (!isdigit(ch = next_char())) if (ch == '-') sgn *= -1;
    x = ch - '0';
    while (isdigit(ch = next_char())) x = x * 10 + (ch - '0');
    return x * sgn;
  }
}

inline namespace Output {

  char buf[BUF_SZ];
  int pos;

  void flush_out() {
    fwrite(buf, 1, pos, stdout);
    pos = 0;
  }

  void write_char(char c) {
    if (pos == BUF_SZ) flush_out();
    buf[pos++] = c;
  }

  void write_int(int x) {
    static char num_buf[100];
    if (x < 0) write_char('-'), x *= -1;
    int len = 0;
    for (; x >= 10; x /= 10) num_buf[len++] = (char) ('0' + (x % 10));
    write_char((char) ('0' + x));
    while (len) write_char(num_buf[--len]);
    write_char('\n');
  }

  void init_output() { assert(atexit(flush_out) == 0); }
}

int n;
vector<int> adj[MAX_N];

struct lazy_segtree {

  pii t[MAX_N << 2];
  bool lazy[MAX_N << 2];
  int cr = -1;

  lazy_segtree() {
    for (int i = 1; i < (n << 2); ++i) lazy[i] = false;
    build(1, 0, n - 1);
  }

  inline void build(int v, int tl, int tr) {
    t[v].second = tr - tl + 1;
    if (tl == tr) return;
    int m = (tl + tr) >> 1;
    build((v << 1), tl, m), build((v << 1) ^ 1, m + 1, tr);
  }

  inline void push(int v, int tl, int tr) {
    if (tl == tr || !lazy[v]) return;
    int l = (v << 1), r = l ^ 1;
    t[l].first = t[r].first = t[v].first, t[l].second = 0, t[r].second = t[v].second;
    lazy[l] = lazy[r] = true, lazy[v] = false;
  }

  inline void upd_rng(int v, int tl, int tr, int l, int r, int c) {
    if (l > r) return;
    push(v, tl, tr);
    if (tl == l && tr == r) lazy[v] = true, t[v] = {c, r == cr};
    else {
      int m = (tl + tr) >> 1;
      upd_rng(v << 1, tl, m, l, min(m, r), c);
      upd_rng((v << 1) ^ 1, m + 1, tr, max(m + 1, l), r, c);
      t[v].second = t[v << 1].second + t[(v << 1) ^ 1].second;
    }
  }

  inline void upd(int l, int r, int c, bool has) {
    cr = has ? r : -1;
    upd_rng(1, 0, n - 1, l, r, c);
  }

  inline int qry_rng(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    push(v, tl, tr);
    if (tl == l && tr == r) return t[v].second;
    int m = (tl + tr) >> 1;
    return qry_rng(v << 1, tl, m, l, min(m, r)) + qry_rng((v << 1) ^ 1, m + 1, tr, max(m + 1, l), r);
  }

  inline int qry_pnt(int v, int tl, int tr, int p) {
    while (tl < tr) {
      push(v, tl, tr);
      int m = (tl + tr) >> 1;
      v <<= 1;
      if (p <= m) tr = m;
      else tl = m + 1, v ^= 1;
    }
    return t[v].first;
  }
};

struct HLD {

  int lvl[MAX_N], sz[MAX_N], up[17][MAX_N], io[MAX_N], po[MAX_N], hc[MAX_N];
  vector<int> ord;
  vector<bool> heavy;
  lazy_segtree t;

  HLD() : heavy(n), t() {
    ord.reserve(n);
    dfs1(0, 0, 0);
    for (int i = 1; i < 17; ++i) for (int j = 0; j < n; ++j) up[i][j] = up[i - 1][up[i - 1][j]];
    dfs2(0, 0);
  }

  inline int dfs1(int v, int p, int l) {
    lvl[v] = l, sz[v] = 1, up[0][v] = p;
    for (int u : adj[v]) if (u != p) sz[v] += dfs1(u, v, l + 1);
    for (int u : adj[v]) if (u != p && sz[u] > sz[v] / 2) heavy[u] = true;
    return sz[v];
  }

  inline void dfs2(int v, int p) {
    io[v] = ord.size(), po[io[v]] = p, ord.push_back(v);
    for (int u : adj[v]) if (u != up[0][v] && heavy[u]) (heavy[v] ? dfs2(u, p) : dfs2(u, io[v])), hc[io[v]] = io[u];
    for (int u : adj[v]) if (u != up[0][v] && !heavy[u]) dfs2(u, io[v]);
  }

  inline int jmp(int a, int u) {
    for (int i = 0; i < 17; ++i) if (u & (1 << i)) a = up[i][a];
    return a;
  }

  inline int lca(int a, int b) {
    if (lvl[a] < lvl[b]) swap(a, b);
    a = jmp(a, lvl[a] - lvl[b]);
    if (a == b) return a;
    for (int i = 16; i >= 0; --i) if (up[i][a] != up[i][b]) a = up[i][a], b = up[i][b];
    return up[0][a];
  }

  inline void upd_down(int a, int b, int c) {
    a = io[a], b = io[b];
    while (a <= b) {
      bool brk = a == b, add = hc[b] >= 0 && t.qry_pnt(1, 0, n - 1, hc[b]) != c;
      if (!heavy[ord[b]]) t.upd(b, b, c, add), b = po[b];
      else {
        int l = max(a, po[b]);
        t.upd(l, b, c, add);
        if (l == a) brk = true;
        b = po[l];
      }
      if (brk) break;
    }
    if (heavy[ord[a]]) t.upd(a - 1, a - 1, t.qry_pnt(1, 0, n - 1, a - 1), 1);
  }

  inline void upd(int a, int b, int c) {
    int top = lca(a, b);
    upd_down(top, a, c), upd_down(top, b, c);
  }

  inline int qry_down(int a, int b) {
    a = io[a], b = io[b];
    int lst = -1, ans = 0;
    while (a <= b) {
      bool brk = a == b;
      int x = t.qry_pnt(1, 0, n - 1, b);
      int val = lst < 0 || lst != x || !x;
      if (val) ++ans;
      if (!heavy[ord[b]]) lst = x, b = po[b];
      else {
        int l = max(a, po[b]);
        ans += t.qry_rng(1, 0, n - 1, l, b - 1);
        if (l == a) brk = true;
        lst = t.qry_pnt(1, 0, n - 1, l), b = po[l];
      }
      if (brk) break;
    }
    return ans;
  }

  inline int qry(int a, int b) {
    int top = lca(a, b);
    return lvl[a] - lvl[top] + lvl[b] - lvl[top] + 2 - qry_down(top, a) - qry_down(top, b);
  }
};

inline void solve() {
  n = read_int();
  int m = read_int();
  for (int i = 0; i < MAX_N; ++i) adj[i].clear();
  for (int i = 0; i < n - 1; ++i) {
    int a = read_int() - 1, b = read_int() - 1;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  HLD hld;
  for (int i = 0; i < m; ++i) {
    int t = read_int(), a = read_int() - 1, b = read_int() - 1;
    if (t == 1) hld.upd(a, b, i + 1);
    else write_int(hld.qry(a, b));
  }
}

int main() {
  init_output();
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t = read_int();
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
