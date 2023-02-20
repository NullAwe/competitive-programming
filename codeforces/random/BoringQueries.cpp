#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int MOD = 1e9 + 7;
const int MAX_A = 200001;
const int SQRT = 447;

ll _p(ll x, ll y) {
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD, y >>= 1;
  }
  return ans;
}

struct max_segtree {

  int n;
  vector<int> t;

  max_segtree() {}

  max_segtree(int n) : n(n), t(2 * n) {}

  void upd(int p, int v) {
    for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
  }

  int qry(int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = max(ans, t[l++]);
      if (r & 1) ans = max(ans, t[--r]);
    }
    return ans;
  }
};

struct spec_segtree {

  int n;
  vector<int> main, back;
  vector<vector<pll>> t;
  vector<vector<ll>> t2;

  spec_segtree(int n, vector<int>& main) : n(n), main(main.begin(), main.end()), back(n), t(4 * n), t2(4 * n) {
    vector<int> last(MAX_A, -1);
    for (int i = 0; i < n; ++i) back[i] = last[main[i]], last[main[i]] = i;
  }

  void build(int p, int tl, int tr) {
    if (tl == tr) {
      t[p].push_back({back[tl], main[tl]});
      t2[p].push_back(main[tl]);
      return;
    }
    int m = (tl + tr) / 2;
    build(2 * p, tl, m), build(2 * p + 1, m + 1, tr);
    for (pll _p : t[2 * p]) t[p].push_back(_p);
    for (pll _p : t[2 * p + 1]) t[p].push_back(_p);
    sort(t[p].begin(), t[p].end());
    ll prod = 1;
    for (pll _p : t[p]) {
      prod = prod * _p.second % MOD;
      t2[p].push_back(prod);
    }
  }

  void build() {
    build(1, 0, n - 1);
  }

  ll qry(int p, int tl, int tr, int l, int r, int ml) {
    if (l > r) return 1;
    if (tl == l && tr == r) {
      int lo = -1, hi = t[p].size();
      while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (t[p][mid].first < ml) lo = mid;
        else hi = mid;
      }
      if (lo < 0) return 1;
      return t2[p][lo];
    }
    int m = (tl + tr) / 2;
    return qry(2 * p, tl, m, l, min(m, r), ml) * qry(2 * p + 1, m + 1, tr, max(m + 1, l), r, ml) % MOD;
  }

  ll qry(int l, int r) {
    return qry(1, 0, n - 1, l, r, l);
  }
};

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> main(n);
  for (int i = 0; i < n; ++i) {
    int tmp = arr[i];
    for (int j = 2; j * j <= tmp; ++j) while (tmp % j == 0) tmp /= j;
    main[i] = tmp > SQRT ? tmp : 1;
  }
  spec_segtree spec(n, main); spec.build();
  vector<int> primes;
  for (int i = 2; i <= SQRT; ++i) {
    bool prime = true;
    for (int j = 2; j < i; ++j) if (i % j == 0) prime = false;
    if (prime) primes.push_back(i);
  }
  int p = primes.size();
  vector<max_segtree> ts(p);
  for (int i = 0; i < p; ++i) ts[i] = max_segtree(n);
  for (int i = 0; i < n; ++i) {
    int tmp = arr[i];
    for (int j = 0; j < p; ++j) {
      int count = 0;
      while (tmp % primes[j] == 0) tmp /= primes[j], ++count;
      ts[j].upd(i, count);
    }
  }
  int q, last = 0; cin >> q;
  for (int i = 0; i < q; ++i) {
    int l, r; cin >> l >> r;
    l = (l + last) % n, r = (r + last) % n;
    if (l > r) swap(l, r);
    ll ans = spec.qry(l, r);
    for (int i = 0; i < p; ++i) {
      int mx = ts[i].qry(l, r + 1);
      ans = ans * _p(primes[i], mx) % MOD;
    }
    cout << ans << '\n';
    last = ans;
  }
  return 0;
}
