#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  string str; cin >> str;
  vector<int> cnt(2), mxs(2);
  int cur = -1, len = 0;
  for (int i = 0; i < n; ++i) {
    ++cnt[str[i] - '0'];
    if (cur < 0) cur = str[i] - '0', len = 1;
    else if (str[i] - '0' == cur) ++len;
    else mxs[cur] = max(mxs[cur], len), cur = str[i] - '0', len = 1;
  }
  mxs[cur] = max(mxs[cur], len);
  cout << max((ll) cnt[0] * cnt[1], max((ll) mxs[0] * mxs[0], (ll) mxs[1] * mxs[1])) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
