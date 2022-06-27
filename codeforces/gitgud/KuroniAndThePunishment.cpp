#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll ans = 0; for (ll num : arr) ans += num & 1;
  shuffle(arr.begin(), arr.end(), default_random_engine{});
  for (int i = 0; i < min(n, 30); ++i) {
    for (int add = -1; add < 2; ++add) {
      ll num = arr[i] + add;
      vector<ll> facts;
      for (ll d = 2; d * d <= num; ++d) {
        if (num % d == 0) facts.push_back(d);
        while (num % d == 0) num /= d;
      }
      if (num > 1) facts.push_back(num);
      for (ll fact : facts) {
        ll comp = 0;
        for (ll x : arr) comp += x < fact ? fact - x : min(x % fact, fact - x % fact);
        ans = min(ans, comp);
      }
    }
  }
  cout << ans << '\n';
  return 0;
}

