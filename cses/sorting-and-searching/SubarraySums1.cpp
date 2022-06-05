#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, k; cin >> n >> k;
  map<ll, int> m; m[0] = 1;
  ll sum = 0, ans = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    sum += x;
    ans += m[sum - k];
    ++m[sum];
  }
  cout << ans << '\n';
}
