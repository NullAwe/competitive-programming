#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m; cin >> n >> m;
  set<int> s;
  for (int i = 0; i < 2 * n; ++i) {
    int x; cin >> x;
    if (s.count(x)) s.erase(x);
    else s.insert(x);
  }
  if (!s.size()) {
    cout << "Bob\n";
    return 0;
  }
  if (m & 1) {
    cout << "Alice\n";
    return 0;
  }
  int del = 0;
  set<int> s2;
  for (int num : s) {
    num %= m / 2;
    if (s2.count(num)) s2.erase(num), ++del;
    else s2.insert(num);
  }
  cout << (s2.size() || del % 2 == 1 ? "Alice\n" : "Bob\n");
  return 0;
}
