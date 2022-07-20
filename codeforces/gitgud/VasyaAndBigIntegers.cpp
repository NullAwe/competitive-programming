#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

vector<int> getZ(string s) {
  int n = s.length();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}

int main() {
  string a, l, r; cin >> a >> l >> r;
  vector<int> zl = getZ(l + "#" + a), zr = getZ(r + "#" + a);
  int n = a.size();
  vector<int> pz(n), az(n);
  pz[0] = a[0] > '0' ? 0 : -1; for (int i = 1; i < n; ++i) pz[i] = a[i] > '0' ? i : pz[i - 1];
  az[n - 1] = a[n - 1] > '0' ? n - 1 : n; for (int i = n - 2; i >= 0; --i) az[i] = a[i] > '0' ? i : az[i + 1];
  vector<int> dp(n); dp[0] = (l.size() == 1 && a[0] >= l[0] && (r.size() > 1 || a[0] <= r[0]));
  int sum = 1, x = -1, y = -1;
  for (int i = max((int) l.size() - 1, 1); i < n; ++i) {
    int ml = zl[i + 2], mr = zr[i + 2];
    int nx = i - l.size(), ny = max(i - (int) r.size(), -1);
    if (ml < l.size() && a[i - l.size() + 1 + ml] < l[ml]) --nx;
    if (i >= r.size() - 1 && mr < r.size() && a[i - r.size() + 1 + mr] > r[mr]) ++ny;
    if (nx < ny) continue;
    while (x < nx) if (a[(++x) + 1] != '0') sum = (sum + dp[x]) % MOD;
    if (y < ny && y < 0) ++y, --sum;
    while (y < ny) if (a[++y] != '0') sum = (sum + MOD - dp[y - 1]) % MOD;
    dp[i] = sum;
    if (a[i] == '0' && l == "0") dp[i] = (dp[i] + dp[i - 1]) % MOD;
  }
  cout << dp[n - 1] << '\n';
  return 0;
}
