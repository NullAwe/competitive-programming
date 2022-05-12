#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  string str; cin >> str;
  vector<int> ans(n * m);
  vector<int> t(m);
  ans[0] = t[0] = (str[0] == '1');
  for (int i = 1; i < n * m; ++i) {
    ans[i] = ans[i - 1] + (str[i] == '1' && !t[i % m]);
    if (str[i] == '1') t[i % m] = 1;
  }
  t = vector<int>(m);
  int first = -1, len0 = 0;
  for (int i = 0; i < n * m; ++i) {
    if (str[i] == '0' && first < 0) continue;
    else if (str[i] == '1' && first < 0) first = i;
    if (str[i] == '0') ++len0;
    else len0 = 0;
    if (len0 >= m) ++t[(i - m + 1 - first) % m];
    ans[i] += (i - first) / m + 1 - t[(i - first + 1) % m];
  }
  for (int num : ans) cout << num << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
