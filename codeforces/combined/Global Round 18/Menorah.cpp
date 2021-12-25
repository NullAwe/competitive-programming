#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string beg, end; cin >> beg >> end;
  if (beg == end) {
    cout << 0 << endl;
    return;
  }
  int bo = 0, eo = 0, to = 0, diff = 0;
  for (int i = 0; i < n; ++i) {
    if (beg[i] == '1') ++bo;
    if (end[i] == '1') ++eo;
    if (beg[i] == '1' && end[i] == '1') ++to;
    if (beg[i] != end[i]) ++diff;
  }
  if (bo == 0 || eo == 0 || (bo != eo && n - bo + 1 != eo)) {
    cout << -1 << endl;
    return;
  }
  int ans = INT_MAX;
  if (bo == eo) ans = diff;
  if (to > 0 && n - bo + 1 == eo) ans = min(ans, n - diff);
  else if (n - bo + 1 == eo) ans = min(ans, n - diff + 1);
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
