#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;

ll pow(ll y) {
  if (y <= 0) return 1;
  ll base = pow(y / 2);
  base = base * base;
  if (y % 2 == 1) base *= 2;
  return base % MOD;
}

void solve() {
  int n, m; cin >> n >> m;
  int z = 0, p = 0;
  for (int i = 0; i < n; ++i) {
    string str; cin >> str;
    for (int j = 0; j < m; ++j) {
      if (str[j] == '0') ++z;
      else ++p;
    }
  }
  ll ans = pow(p);
  if (z == 0) --ans;
  cout << (ans + MOD) % MOD << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
