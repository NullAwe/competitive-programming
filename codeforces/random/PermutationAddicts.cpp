#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) --arr[i];
  int k = -1;
  for (int i = 0; i < n; ++i) if (arr[i] > i) k = i;
  vector<int> lg;
  vector<vector<int>> inds(n);
  for (int i = 0; i < n; ++i) {
    if (arr[i] == -1 || arr[i] == n) lg.push_back(i);
    else inds[arr[i]].push_back(i);
  }
  cout << k + 1 << '\n';
  while (lg.size()) {
    vector<int> nlg;
    for (int i : lg) {
      if (inds[i].size()) {
        for (int num : lg) if (num != i) cout << num + 1 << ' ';
        cout << i + 1 << ' ';
        for (int j : inds[i]) nlg.push_back(j);
        break;
      }
    }
    if (!nlg.size()) break;
    lg = nlg;
  }
  for (int num : lg) cout << num + 1 << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
