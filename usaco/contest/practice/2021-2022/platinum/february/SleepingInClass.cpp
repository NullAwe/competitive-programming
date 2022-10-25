#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pli pair<ll, int>

const int MX_STP = 100000;
const vector<pii> tries = {{2, 1}, {5, 3}, {11, 7}, {17, 13}};

inline ll add(ll a, ll b, ll mod) {
  return a + b >= mod ? a + b - mod : a + b;
}

inline ll mult(ll a, ll b, ll mod) {
  ll ans = 0;
  while (b) {
    if (b & 1) ans = add(ans, a, mod);
    a = add(a, a, mod);
    b >>= 1;
  }
  return ans;
}

inline ll f(ll x, ll c, ll mod) {
  return add(mult(x, x, mod), c, mod);
}

inline ll rho(ll n, ll x0 = 2, ll c = 1) {
  ll x = x0, y = x0, g = 1, steps = 0;
  while (g == 1 && steps < MX_STP)
    x = f(x, c, n), y = f(f(y, c, n), c, n), g = gcd(abs(x - y), n), ++steps;
  return g;
}

vector<ll> pf(ll n) {
  vector<ll> ans;
  if (n == 1) return ans;
  ll fact = 1;
  if (n < MX_STP) {
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) fact = i;
  } else {
    for (pii t : tries) {
      fact = rho(n, t.first, t.second);
      if (fact > 1 && fact < n) break;
    }
  }
  if (fact == 1 || fact == n) ans.push_back(n);
  else {
    ans = pf(fact);
    for (ll num : pf(n / fact)) ans.push_back(num);
  }
  return ans;
}

int n;
vector<ll> p;
map<ll, int> ans;

void precomp() {
  vector<ll> ps = pf(p.back());
  sort(ps.begin(), ps.end());
  if (!ps.size()) return;
  vector<pli> exp(1, {ps[0], 1});
  for (int i = 1; i < ps.size(); ++i) {
    if (ps[i] == ps[i - 1]) ++exp[exp.size() - 1].second;
    else exp.push_back({ps[i], 1});
  }
  for (ll num : p) ++ans[num];
  vector<ll> facts(1, 1);
  for (pli prime : exp) {
    vector<ll> next(facts.size() * (prime.second + 1));
    ll mult = 1;
    for (int i = 0; i <= prime.second; ++i) {
      for (int j = 0; j < facts.size(); ++j) next[i * facts.size() + j] = facts[j] * mult;
      mult *= prime.first;
    }
    facts = next;
  }
  sort(facts.begin(), facts.end()), reverse(facts.begin(), facts.end());
  for (pli prime : exp) for (ll num : facts)
    if (num % prime.first == 0) ans[num / prime.first] += ans[num];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  p.resize(n);
  for (int i = 0; i < n; ++i) { ll x; cin >> x; p[i] = p[max(i - 1, 0)] + x; }
  for (int i = 0; i < n; ++i) p[i] = gcd(p[n - 1], p[i]);
  precomp();
  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    ll x; cin >> x;
    if (p.back() % x) cout << -1 << '\n';
    else cout << (n + p.back() / x - 2 * ans[x]) << '\n';
  }
  return 0;
}
