#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, m; cin >> n >> m;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<ll> dmgf(n + 1); for (int i = 1; i < n; ++i) dmgf[i + 1] = dmgf[i] + max(arr[i - 1] - arr[i], 0);
  vector<ll> dmgb(n + 1); for (int i = n - 2; i >= 0; --i) dmgb[i] = dmgb[i + 1] + max(arr[i + 1] - arr[i], 0);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    if (a < b) cout << dmgf[b + 1] - dmgf[a + 1] << '\n';
    else cout << dmgb[b] - dmgb[a] << '\n';
  }
  return 0;
}
