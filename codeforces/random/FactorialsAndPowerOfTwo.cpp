#include <bits/stdc++.h>
using namespace std;

#define ll long long

int count(ll x) {
  int ans = 0;
  while (x > 0) {
    ans += x & 1;
    x >>= 1;
  }
  return ans;
}

void solve() {
  ll n; cin >> n;
  vector<ll> fact; fact.push_back(1);
  for (int i = 1; ; ++i) {
    if (fact[i - 1] * i > n) break;
    fact.push_back(fact[i - 1] * i);
  }
  int ans = count(n);
  for (int i = 0; i < (1 << fact.size()); ++i) {
    ll sum = 0;
    for (int j = 0; j < fact.size(); ++j) if ((1 << j) & i) sum += fact[j];
    if (sum > n) continue;
    ans = min(ans, count(i) + count(n - sum));
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
