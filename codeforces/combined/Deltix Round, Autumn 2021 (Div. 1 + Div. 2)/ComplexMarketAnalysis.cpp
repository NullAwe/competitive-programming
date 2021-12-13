#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_X = 1000001;

vector<bool> composite(MAX_X, false);

void solve() {
  int n, e; cin >> n >> e;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll ans = 0;
  for (int i = 0; i < e; ++i) {
    vector<pair<int, int>> v;
    for (int j = i; j < n; j += e) {
      if (arr[j] != 1) {
        v.push_back({arr[j], 0});
      } else {
        int ones = 0;
        while (j < n && arr[j] == 1) {
          ++ones;
          j += e;
        }
        v.push_back({1, ones});
        j -= e;
      }
    }
    for (int j = 0; j < v.size(); ++j) {
      if (composite[v[j].first]) continue;
      ll l = 0, r = 0;
      if (j > 0 && v[j - 1].first == 1) l = v[j - 1].second;
      if (j < v.size() - 1 && v[j + 1].first == 1) r = v[j + 1].second;
      ans += (l + 1) * (r + 1) - 1;
    }
  }
  // Output:
  cout << ans << endl;
}

int main() {
  composite[1] = true;
  for (int i = 2; i < MAX_X; ++i) {
    if (composite[i]) continue;
    for (int j = i + i; j < MAX_X; j += i) composite[j] = true;
  }
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
