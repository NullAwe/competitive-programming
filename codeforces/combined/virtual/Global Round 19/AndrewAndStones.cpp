#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int ones = 0; for (int i = 1; i < n - 1; ++i) if (arr[i] == 1) ++ones;
  int odds = 0; for (int i = 1; i < n - 1; ++i) if (arr[i] % 2) ++odds;
  ll sum = 0; for (int i = 1; i < n - 1; ++i) sum += arr[i];
  if (ones == n - 2 || n == 3 && odds == 1) cout << -1 << endl;
  else cout << (sum + odds) / 2 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

