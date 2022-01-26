#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

inline ll p(ll x, ll y) {
  ll res = 1;
  while (y > 0) {
    if (y & 1) res = res * x % MOD;
    x  = x * x % MOD;
    y >>= 1;
  }
  return res;
}

inline ll inv(ll x) { return p(x, MOD - 2); }

int main() {
  string begin, end; cin >> begin >> end;
  ll shared = 0;
  int sh = 0;
  for (int i = 0; i < begin.size(); ++i) {
    if (begin[i] != end[i]) break;
    shared = (shared * 10 + begin[i] - '0') % MOD;
    ++sh;
  }
  int n = begin.size() - sh;
  begin = begin.substr(sh, n);
  end = end.substr(sh, n);
  // Mods powers of 10:
  ll tm[n + 1]; tm[0] = 1;
  for (int i = 1; i <= n; ++i) tm[i] = tm[i - 1] * 10 % MOD;
  shared = shared % MOD;
  // Mods start prefixes with 7 replacing the last number:
  ll bm[n + 1], cur = shared; bm[0] = 0, bm[1] = (shared * tm[n] + 4 * tm[n - 1]) % MOD;
  for (int i = 2; i <= n; ++i) {
    cur = (cur * 10 + begin[i - 2] - '0') % MOD;
    bm[i] = ((cur * 10 + 7) % MOD) * tm[n - i] % MOD;
  }
  // Mods end prefixes with 4 replacing the last number:
  ll em[n + 1]; em[0] = 0, em[1] = (shared * tm[n] + 4 * tm[n - 1]) % MOD; cur = shared;
  for (int i = 2; i <= n; ++i) {
    cur = (cur * 10 + end[i - 2] - '0') % MOD;
    em[i] = ((cur * 10 + 4) % MOD) * tm[n - i] % MOD;
  }
  ll dp4[n + 1], dp7[n + 1], cur2 = 0; dp4[0] = dp7[0] = 0; cur = 0;
  for (int i = 1; i <= n; ++i) cur = (cur * 10 + 4) % MOD, cur2 = (cur2 * 10 + 7) % MOD, dp4[i] = cur, dp7[i] = cur2;
  // Mods x 4's to x 7's answers and sums:
  ll dpm[n + 1], dps[n + 1]; dpm[0] = dps[0] = 0, dpm[1] = 28, dps[1] = 11;
  for (int i = 2; i <= n; ++i) {
    ll f = 4 * tm[i - 1] % MOD, s = 7 * tm[i - 1] % MOD, num = p(2, i - 1);
    dpm[i] = dpm[i - 1] + ((dps[i - 1] * 2 - dp4[i - 1] - dp7[i - 1] + 2 * MOD) % MOD) * f % MOD + (f * f % MOD) * (num + MOD - 1) % MOD;
    dpm[i] %= MOD;
    dpm[i] += dpm[i - 1] + ((dps[i - 1] * 2 - dp4[i - 1] - dp7[i - 1] + 2 * MOD) % MOD) * s % MOD + (s * s % MOD) * (num + MOD - 1) % MOD;
    dpm[i] %= MOD;
    dpm[i] += ((f + dp7[i - 1]) % MOD) * ((s + dp4[i - 1]) % MOD) % MOD;
    dps[i] = 2 * dps[i - 1] % MOD;
    dps[i] += f * num % MOD;
    dps[i] %= MOD;
    dps[i] += s * num % MOD;
    dps[i] %= MOD;
  }
  // Does each chunk (digit dynamic programming):
  int ind = n - 1;
  while (ind > 0 && begin[ind] == '4') --ind;
  ll ans = dpm[n - ind - 1] + ((dps[n - ind - 1] * 2 - dp4[n - ind - 1] - dp7[n - ind - 1] + 2 * MOD) % MOD) * bm[ind + 1] % MOD + (bm[ind + 1] * bm[ind + 1] % MOD) * (p(2, n - ind - 1) + MOD - 1) % MOD;
  ans %= MOD;
  ll last = (bm[ind + 1] + dp7[n - ind - 1]) % MOD;
  while (ind > 0) {
    --ind;
    while (ind > 0 && begin[ind] == '7') --ind;
    if (ind == 0) break;
    ans += last * (bm[ind + 1] + dp4[n - ind - 1]) % MOD;
    ans %= MOD;
    ans += dpm[n - ind - 1] + ((dps[n - ind - 1] * 2 - dp4[n - ind - 1] - dp7[n - ind - 1] + 2 * MOD) % MOD) * bm[ind + 1] % MOD + (bm[ind + 1] * bm[ind + 1] % MOD) * (p(2, n - ind - 1) + MOD - 1) % MOD;
    ans %= MOD;
    last = (bm[ind + 1] + dp7[n - ind - 1]) % MOD;
  }
  ind = 0;
  while (ind < n) {
    ++ind;
    while (ind < n && end[ind] == '4') ++ind;
    if (ind >= n) break;
    ans += last * (em[ind + 1] + dp4[n - ind - 1]) % MOD;
    ans %= MOD;
    ans += dpm[n - ind - 1] + ((dps[n - ind - 1] * 2 - dp4[n - ind - 1] - dp7[n - ind - 1] + 2 * MOD) % MOD) * em[ind + 1] % MOD + (em[ind + 1] * em[ind + 1] % MOD) * (p(2, n - ind - 1) + MOD - 1) % MOD;
    ans %= MOD;
    last = (em[ind + 1] + dp7[n - ind - 1]) % MOD;
  }
  ans = (ans + last * (em[n] - 4 + end[n - 1] - '0')) % MOD;
  // Output:
  cout << ans << endl;
}
