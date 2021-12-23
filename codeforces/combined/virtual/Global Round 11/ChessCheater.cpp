#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  string str; cin >> str;
  vector<int> a;
  int beg = 0, cur = 0;
  bool started = false;
  for (int i = 0; i < str.size(); ++i) {
    if (!started && str[i] == 'L') {
      ++beg;
      continue;
    }
    if (!started) started = true;
    if (str[i] == 'W') {
      if (cur) a.push_back(cur);
      cur = 0;
    } else ++cur;
  }
  // Takes care of the edge case where there are no 'W's:
  if (!started) {
    cout << max(min(beg, k) * 2 - 1, 0) << endl;
    return;
  }
  sort(a.begin(), a.end());
  int ans = 0;
  for (int i = 0; i < a.size() && k > 0; ++i) {
    ans += min(a[i], k) * 2;
    if (k >= a[i]) ++ans;
    k -= min(a[i], k);
  }
  if (k > 0) ans += min(cur + beg, k) * 2;
  if (beg == 0) ++ans;
  for (int i = 1; i < str.size(); ++i) {
    if (str[i] == 'W') ++ans;
    if (str[i] == 'W' && str[i - 1] == 'W') ++ans;
  }
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
