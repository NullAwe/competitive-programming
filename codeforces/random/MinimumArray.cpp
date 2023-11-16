#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> diff(n - 1); for (int i = 0; i < n - 1; ++i) diff[i] = arr[i] - arr[i + 1];
  int beg = arr[0];
  int q; cin >> q;
  vector<int> cd = diff;
  int cb = beg;
  set<int> changed;
  for (int i = 0; i < q; ++i) {
    int x, y, z; cin >> x >> y >> z; --x, --y;
    if (x == 0) beg += z;
    else {
      diff[x - 1] -= z;
      changed.insert(x - 1);
    }
    if (y < n - 1) {
      diff[y] += z;
      changed.insert(y);
    }
    if (beg < cb) {
      cb = beg;
      for (int c : changed) cd[c] = diff[c];
      changed.clear();
      continue;
    }
    if (beg > cb) continue;
    while (changed.size()) {
      int c = *changed.begin();
      if (cd[c] == diff[c]) {
        changed.erase(c);
        continue;
      }
      if (diff[c] > cd[c]) {
        cb = beg;
        for (int c2 : changed) cd[c2] = diff[c2];
        changed.clear();
      }
      break;
    }
  }
  cout << cb;
  for (int num : cd) {
    cb -= num;
    cout << ' ' << cb;
  }
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}