#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void solve() {
  int n; cin >> n;
  string a, b; cin >> a >> b;
  vector<pii> ops;
  int cnt = 0;
  vector<int> cnt2(2);
  for (int i = 0; i < n; ++i) if (a[i] == '1') ops.push_back({i + 1, i + 1}), ++cnt;
  for (int i = 0; i < n; ++i) {
    if ((cnt - (a[i] - '0')) & 1) b[i] = ('0' + '1') - b[i];
    ++cnt2[b[i] - '0'];
  }
  if (cnt2[0] && cnt2[1]) cout << "NO\n";
  else {
    cout << "YES\n";
    if (cnt2[1]) ops.push_back({1, 1}), ops.push_back({2, n}), ops.push_back({1, n});
    cout << ops.size() << '\n';
    for (pii op : ops) cout << op.first << ' ' << op.second << '\n';
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
