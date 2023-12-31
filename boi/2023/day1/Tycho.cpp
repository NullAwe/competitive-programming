#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define ll long long

const ll MAX = 2000000LL * 2000000LL;

ll b, p;
int d, n;
vector<ll> arr;
vector<ll> modulos;
vector<ll> dp;
vector<ll> t;

int idx_of(ll x) {
  return lower_bound(modulos.begin(), modulos.end(), x % p) - modulos.begin();
}

ll get_int(int i, ll mod) {
  ll loc = (MAX / p + 1) * p + mod;
  return dp[i] + (loc - arr[i] - 1) / p * d + loc - arr[i] + (p - (loc - arr[i]) % p) % p;
}

ll fnorm(int i, int j) {
  if (i == j) return dp[i];
  return dp[i] + (arr[j] - arr[i] - 1) / p * d + arr[j] - arr[i];
}

void add_line(int l, int r, ll yint, int v = 1, int tl = 0, int tr = n - 1) {
  if (l > r) return;
  if (l == tl && tr == r) {
    t[v] = min(t[v], yint);
    return;
  }
  int m = (tl + tr) / 2;
  add_line(l, min(m, r), yint, 2 * v, tl, m);
  add_line(max(m + 1, l), r, yint, 2 * v + 1, m + 1, tr);
}

ll get(int x, int v = 1, int l = 0, int r = n - 1) {
  if (l == r) return t[v];
  int m = (l + r) / 2;
  if (x <= m) return min(t[v], get(x, 2 * v, l, m));
  else return min(t[v], get(x, 2 * v + 1, m + 1, r));
}

int main() {
  cin >> b >> p >> d >> n; n += 2;
  arr.resize(n); for (int i = 0; i < n - 2; ++i) cin >> arr[i + 1];
  arr[0] = 0, arr.back() = b;
  for (ll num : arr) modulos.push_back(num % p);
  sort(modulos.begin(), modulos.end());
  t.resize(4 * n, LLONG_MAX);
  dp.resize(n);
  dp[0] = 0;
  add_line(0, 0, get_int(0, 0));
  add_line(1, n - 1, get_int(0, 1));
  for (int i = 1; i < n; ++i) {
    dp[i] = get(idx_of(arr[i]));
    ll loc = (MAX / p + 1) * p + arr[i] % p;
    dp[i] -= (loc - arr[i]) * (d + p) / p;
    if (arr[i] % p == 0) {
      add_line(0, 0, get_int(i, 0));
      add_line(1, n - 1, get_int(i, 1));
    } else {
      add_line(0, idx_of(arr[i]), get_int(i, 0));
      add_line(idx_of(arr[i]) + 1, n - 1, get_int(i, arr[i] % p + 1));
    }
  }
  ll ans = LLONG_MAX;
  for (int i = 0; i < n; ++i) ans = min(ans, fnorm(i, n - 1));
  cout << ans << '\n';
  return 0;
}