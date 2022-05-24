#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  int s = 0, e = INT_MAX;
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    s = max(s, a), e = min(e, b);
  }
  cout << max(s - e, 0) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
