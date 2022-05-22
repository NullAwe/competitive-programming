#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  set<int> once, twice;
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    if (once.count(a)) once.erase(a), twice.insert(a);
    else if (!twice.count(a)) once.insert(a);
  }
  cout << (once.size() + 1) / 2 + twice.size() << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
