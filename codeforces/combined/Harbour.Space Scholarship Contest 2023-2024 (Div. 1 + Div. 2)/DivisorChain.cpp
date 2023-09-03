#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n; cin >> n;
  int beg = n;
  vector<int> strat;
  while (true) {
    int tmp = n, cnt = 1;
    while (tmp % 2 == 0) tmp /= 2, cnt *= 2;
    if (cnt == n) break;
    strat.push_back(cnt);
    n -= cnt;
  }
  while (n > 1) {
    strat.push_back(n / 2);
    n /= 2;
  }
  cout << (int) strat.size() + 1 << '\n';
  int cur = beg;
  cout << cur;
  for (int num : strat) {
    cur -= num;
    cout << ' ' << cur;
  }
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
