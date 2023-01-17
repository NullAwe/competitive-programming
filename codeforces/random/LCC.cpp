#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MOD = 998244353;

inline ll _p(ll x, ll y) {
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD, y >>= 1;
  }
  return ans;
}

inline ll inv(ll x) { return _p(x, MOD - 2); }

struct lazy_segment_tree {

  vector<ll> t, lazy;
  int n;

  lazy_segment_tree() {}

  lazy_segment_tree(int n) : n(n), t(4 * n), lazy(4 * n, 1) {}

  inline void push(int v, int tl, int tr) {
    if (tl == tr) return;
    int l = 2 * v, r = 2 * v + 1;
    lazy[l] = lazy[l] * lazy[v] % MOD;
    lazy[r] = lazy[r] * lazy[v] % MOD;
    t[l] = (t[l] * lazy[v]) % MOD;
    t[r] = (t[r] * lazy[v]) % MOD;
    lazy[v] = 1;
  }

  void upd(int v, int tl, int tr, int p, ll val) {
    push(v, tl, tr);
    if (tl == tr) {
      t[v] = val;
      return;
    }
    int m = (tl + tr) / 2;
    if (p <= m) upd(2 * v, tl, m, p, val);
    else upd(2 * v + 1, m + 1, tr, p, val);
    t[v] = (t[2 * v] + t[2 * v + 1]) % MOD;
  }

  void upd(int v, int tl, int tr, int l, int r, ll mult) {
    if (l > r) return;
    push(v, tl, tr);
    if (tl == l && tr == r) {
      t[v] = (t[v] * mult) % MOD;
      lazy[v] = mult;
      return;
    }
    int m = (tl + tr) / 2;
    upd(2 * v, tl, m, l, min(m, r), mult);
    upd(2 * v + 1, m + 1, tr, max(m + 1, l), r, mult);
    t[v] = (t[2 * v] + t[2 * v + 1]) % MOD;
  }

  ll qry(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    push(v, tl, tr);
    if (tl == l && tr == r) return t[v];
    int m = (tl + tr) / 2;
    return (qry(2 * v, tl, m, l, min(m, r)) + qry(2 * v + 1, m + 1, tr, max(m + 1, l), r)) % MOD;
  }
};

struct fraction {

  ll a, b;

  fraction() : a(0), b(1) {}

  fraction(ll a, ll b) : a(a), b(b) {}

  inline bool operator==(const fraction& rhs) {
    return a * rhs.b == b * rhs.a;
  }

  inline bool operator!=(const fraction& rhs) {
    return !(fraction(a, b) == rhs);
  }

  inline bool operator<(const fraction& rhs) {
    return a * rhs.b < b * rhs.a;
  }
};

struct proton {

  ll pos, vel, p;

  proton() {}
};

int n;
vector<proton> arr;

struct prefix_products {

  vector<ll> left, right;

  prefix_products() {
    left.resize(2 * n), right.resize(2 * n);
    ll percent = inv(100);
    for (int i = 0; i < n; ++i) {
      left[i + n] = (100 - arr[i].p) * percent % MOD;
      right[i + n] = arr[i].p * percent % MOD;
    }
    for (int i = n - 1; i > 0; --i) {
      left[i] = (left[2 * i] * left[2 * i + 1]) % MOD;
      right[i] = (right[2 * i] * right[2 * i + 1]) % MOD;
    }
  }

  ll qryLeft(int a, int b) {
    ll ans = 1;
    for (a += n, b += n + 1; a < b; a >>= 1, b >>= 1) {
      if (a & 1) ans = ans * left[a++] % MOD;
      if (b & 1) ans = ans * left[--b] % MOD;
    }
    return ans;
  }

  ll qryRight(int a, int b) {
    ll ans = 1;
    for (a += n, b += n + 1; a < b; a >>= 1, b >>= 1) {
      if (a & 1) ans = ans * right[a++] % MOD;
      if (b & 1) ans = ans * right[--b] % MOD;
    }
    return ans;
  }
};

struct probability_maintainer {

  lazy_segment_tree segtree;
  prefix_products pre;

  set<pair<pii, pii>> s;
  ll ans = 1;

  probability_maintainer() : segtree(n), pre() {
    for (int i = 0; i < n; ++i) s.insert({{i, i}, {i, i + 1}});
    for (int i = 0; i < n; ++i) segtree.upd(1, 0, n, i, pre.qryRight(i, i));
  }

  void add(int i) {
    if (ans == 0) return;
    auto cur = s.lower_bound({{i, i}, {i, i}});
    auto bef = prev(cur);
    s.erase(cur), s.erase(bef);
    pii sa = bef->first, sb = cur->first;
    int a = sa.first, b = sa.second, c = sb.first, d = sb.second;
    pii ra = bef->second, rb = cur->second;
    int w = ra.first, x = ra.second, y = rb.first, z = rb.second;
    ll tl = segtree.qry(1, 0, n, w, min(x, b));
    if (x == b + 1) tl += pre.qryLeft(a, b);
    ll tr = segtree.qry(1, 0, n, y, min(z, d));
    if (z == d + 1) tr += pre.qryLeft(c, d);
    ans = ans * inv(tl * tr % MOD) % MOD;
    if (x <= b && y > c) {
      ans = 0;
      return;
    }
    segtree.upd(1, 0, n, a, b, pre.qryRight(c, d));
    segtree.upd(1, 0, n, c, d, pre.qryLeft(a, b));
    int nw = y > c ? y : w;
    int nx = x <= b ? x : z;
    ll ad = segtree.qry(1, 0, n, nw, min(nx, d));
    if (nx == d + 1) ad += pre.qryLeft(a, d);
    ans = ans * ad % MOD;
    s.insert({{a, d}, {nw, nx}});
  }

  void addRestriction(int i) {
    if (ans == 0) return;
    auto cur = --s.lower_bound({{i, i}, {i, i}});
    s.erase(cur);
    int a = cur->first.first, b = cur->first.second;
    int w = cur->second.first, x = cur->second.second;
    ll tl = segtree.qry(1, 0, n, w, min(x, b));
    if (x == b + 1) tl += pre.qryLeft(a, b);
    ans = ans * inv(tl) % MOD;
    if (arr[i].vel > arr[i - 1].vel) {
      if (w > i) {
        ans = 0;
        return;
      }
      x = min(x, i);
    } else {
      if (x < i) {
        ans = 0;
        return;
      }
      w = max(w, i);
    }
    tl = segtree.qry(1, 0, n, w, min(x, b));
    if (x == b + 1) tl += pre.qryLeft(a, b);
    ans = ans * tl % MOD;
    s.insert({{a, b}, {w, x}});
  }

  ll getProbability() {
    return ans;
  }
};

int main() {
  ll percent = inv(100);
  cin >> n;
  arr.resize(n);
  for (int i = 0; i < n; ++i) cin >> arr[i].pos >> arr[i].vel >> arr[i].p;
  vector<pair<fraction, int>> ways;
  for (int i = 1; i < n; ++i) {
    ll d = arr[i].pos - arr[i - 1].pos;
    ll v = arr[i].vel + arr[i - 1].vel;
    ways.push_back({fraction(d, v), i});
    v = abs(arr[i].vel - arr[i - 1].vel);
    if (v) ways.push_back({fraction(d, v), i});
  }
  sort(ways.begin(), ways.end(), [&](pair<fraction, int> a, pair<fraction, int> b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
  });
  probability_maintainer maintainer;
  vector<bool> done(n);
  ll ans = 0;
  for (int i = 0; i < ways.size(); ++i) {
    ll prob = maintainer.getProbability();
    if (!prob) break;
    int mx;
    for (mx = i; mx < ways.size(); ++mx) if (ways[i].first != ways[mx].first) break;
    fraction time = ways[i].first;
    ll colt = time.a * inv(time.b) % MOD;
    for (int j = i; j < mx; ++j) {
      int i = ways[j].second;
      if (!done[i]) maintainer.add(i);
      else maintainer.addRestriction(i);
      done[i] = true;
    }
    i = mx - 1;
    ll prob2 = maintainer.getProbability();
    ll left = (prob - prob2 + MOD) % MOD;
    ans = (ans + left * colt) % MOD;
  }
  cout << ans << '\n';
  return 0;
}