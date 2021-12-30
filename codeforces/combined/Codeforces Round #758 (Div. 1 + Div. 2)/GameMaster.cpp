#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i].first;
  for (int i = 0; i < n; ++i) cin >> v[i].second;
  map<pair<int, int>, int> m;
  for (int i = 0; i < n; ++i) m[v[i]] = i;
  vector<pair<int, int>> sorted = v;
  sort(sorted.begin(), sorted.end());
  set<int> s;
  for (int i = 0; i < n; ++i) s.insert(v[i].second);
  set<int> perm, hold;
  int ind = -1;
  for (int i = 0; i < n - 1; ++i) {
    pair<int, int> top = sorted[i];
    int val = *s.begin();
    perm.insert(val);
    s.erase(val);
    if (hold.count(val)) {
      hold.erase(val);
      perm.erase(val);
    }
    if (!perm.count(top.second)) hold.insert(top.second);
    if (hold.size() == 0) ind = i;
  }
  vector<int> ans(n);
  if (ind == n - 1) ind = -1;
  for (int i = ind + 1; i < n; ++i) ans[m[sorted[i]]] = 1;
  // Output:
  for (int num : ans) cout << num;
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
