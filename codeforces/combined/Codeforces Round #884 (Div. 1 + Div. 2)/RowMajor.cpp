#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, my, pr = 0; cin >> n;
  for (my = 1;; ++my) if (n % my > 0) break;
  int on = 0;
  while (pr < n) {
    cout << (char) (on + 'a');
    ++pr, on = (on + 1) % my;
  }
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
