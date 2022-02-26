#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n, q; cin >> n >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  map<int, int> m;
  for (int num : arr) ++m[num];
  vector<vector<int>> r(n);
  for (auto& [a, b] : m) r[b].push_back(a);
  for (int i = 0; i < n; ++i) reverse(r[i].begin(), r[i].end());
  vector<pair<int, int>> bad; bad.reserve(2 * q);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b;
    bad.push_back({a, b});
    bad.push_back({b, a});
  }
  sort(bad.begin(), bad.end());
  ll ans = 0;
  for (int first = 1; first < n; ++first) {
    for (int a : r[first]) {
      for (int next = 1; next <= first; ++next) {
        ll t = first + next;
        for (int b : r[next]) {
          if (a == b) break;
          if (!binary_search(bad.begin(), bad.end(), pair<int, int>{a, b})) {
            ans = max(ans, t * (a + b));
            break;
          }
        }
      }
    }
  }
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

