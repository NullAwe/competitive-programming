#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n, q; cin >> n >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  vector<ll> p(n + 1); for (int i = 0; i < n; ++i) p[i + 1] = p[i] + arr[i];
  for (int i = 0; i < q; ++i) {
    int x, y; cin >> x >> y;
    cout << p[n - x + y] - p[n - x] << '\n';
  }
}

int main() {
  solve();
  return 0;
}