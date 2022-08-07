#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void solve() {
  int n; cin >> n;
  vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
  multiset<pii> as, bs;
  for (int i = 1; i < n; ++i) as.insert({min(a[i], a[i - 1]), max(a[i], a[i - 1])}),
    bs.insert({min(b[i], b[i - 1]), max(b[i], b[i - 1])});
  if (as != bs || a[0] != b[0] || a[n - 1] != b[n - 1]) {
    cout << "NO\n";
    return;
  }
  vector<pii> ops;
  for (int i = 0; i < n - 1; ++i) {
    if (a[i + 1] == b[i + 1]) continue;
    for (int j = i + 1; j < n; ++j) {
      if (a[j] == b[i] && a[j - 1] == b[i + 1]) {
        ops.push_back({i, j});
        reverse(a.begin() + i, a.begin() + j + 1);
        break;
      }
    }
    if (a[i + 1] == b[i + 1]) continue;
    vector<int> inds;
    for (int j = i + 1; j < n; ++j) if (a[j - 1] == b[i] && a[j] == b[i + 1]) inds.push_back(j - 1);
    for (int ind : inds) {
      set<int> l;
      for (int j = i; j < ind; ++j) l.insert(a[j]);
      int find = -1;
      for (int j = ind + 1; j < n; ++j) if (l.count(a[j])) find = a[j];
      if (find < 0) continue;
      int x = 0, y = 0;
      for (int j = i; j < ind; ++j) if (a[j] == find) x = j;
      for (int j = ind + 1; j < n; ++j) if (a[j] == find) y = j;
      ops.push_back({x, y});
      reverse(a.begin() + x, a.begin() + y + 1);
      for (int j = i + 1; j < n; ++j) {
        if (a[j] == b[i] && a[j - 1] == b[i + 1]) {
          ops.push_back({i, j});
          reverse(a.begin() + i, a.begin() + j + 1);
          break;
        }
      }
      break;
    }
  }
  cout << "YES\n";
  cout << ops.size() << '\n';
  for (pair<int, int> p : ops) cout << p.first + 1 << ' ' << p.second + 1 << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

