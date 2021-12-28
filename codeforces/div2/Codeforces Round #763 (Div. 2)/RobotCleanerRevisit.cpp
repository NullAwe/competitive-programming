#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;

inline ll _p(ll x, ll y) {
  ll res = 1;
  while (y > 0) {
    if (y & 1) res = res * x % MOD;
    x = (x * x) % MOD;
    y >>= 1;
  }
  return res;
}

inline ll inv(ll x) { return _p(x, MOD - 2); }

void add(ll& a, ll& b, ll c, ll d) {
  if (b == d - 1) a = a * 100 % MOD;
  a = (a + c) % MOD;
  if (b < d) b = d;
}

void solve() {
  int n, m, rb, cb, rd, cd, p; cin >> n >> m >> rb >> cb >> rd >> cd >> p;
  int beginR, beginC, rc = 1, cc = 1, countTimes = 0, curR = rb, curC = cb, time = 0;
  ll num = 0, dem = 0;
  do {
    if (curR >= n) rc = -1;
    else if (curR <= 1) rc = 1;
    if (curC >= m) cc = -1;
    else if (curC <= 1) cc = 1;
    if (time == 0) beginR = rc, beginC = cc;
    if (curR == rb && curC == cb && rc == beginR && cc == beginC && time > 0) break;
    if (curR == rd || curC == cd) {
      add(num, dem, (time * _p(100LL - p, countTimes) % MOD) * p % MOD, countTimes + 1);
      ++countTimes;
    }
    ++time;
    curR += rc;
    curC += cc;
  } while (curR != rb || curC != cb || rc != beginR || cc != beginC);
  add(num, dem, _p(100LL - p, countTimes) * time % MOD, countTimes); dem -= countTimes;
  ll modTop = _p(100LL, countTimes) - _p(100LL - p, countTimes);
  while (modTop < 0) modTop += MOD;
  // Output:
  cout << ((num * inv(_p(100LL, dem)) % MOD) * inv(modTop) % MOD) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
