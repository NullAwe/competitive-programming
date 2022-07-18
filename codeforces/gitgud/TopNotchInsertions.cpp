#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MOD = 998244353;
const int MAX_N = 4e5 + 1;

vector<ll> fact(MAX_N);
vector<int> t(MAX_N);

void modify(int n, int p, int v) { for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1]; }

int query(int n, int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

ll p(ll x, ll y) {
  if (!y) return 1;
  ll b = p(x, y >> 1);
  b = b * b % MOD;
  if (y & 1) b *= x;
  return b % MOD;
}

ll inv(ll x) { return p(x, MOD - 2); }

ll nCr(ll n, ll r) { return (fact[n] * inv(fact[r]) % MOD) * inv(fact[n - r]) % MOD; }

void solve() {
  int n, m; cin >> n >> m;
  vector<pii> ops(m); for (int i = 0; i < m; ++i) cin >> ops[i].first >> ops[i].second;
  reverse(ops.begin(), ops.end());
  vector<pii> places;
  vector<int> add;
  for (int i = 0; i < m; ++i) {
    int lo = ops[i].second - 1, hi = n;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2, moved = mid - ops[i].second + 1, has = query(n, 0, mid + 1);
      if (has > moved || (has == moved && !t[mid + n])) lo = mid;
      else hi = mid;
    }
    modify(n, lo, 1), add.push_back(lo);
    places.push_back({lo, ops[i].first - 1});
  }
  sort(places.begin(), places.end());
  int out = 0;
  for (int i = 0; i < places.size(); ++i) {
    pii p = places[i];
    if (p.first == n - 1) break;
    if (i == places.size() - 1 || places[i + 1].first != p.first + 1 || places[i + 1].second < p.second) ++out;
  }
  cout << nCr(2 * n - out - 1, n) << '\n';
  for (int num : add) modify(n, num, 0);
}

int main() {
  fact[0] = 1;
  for (int i = 1; i < MAX_N; ++i) fact[i] = fact[i - 1] * i % MOD;
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
