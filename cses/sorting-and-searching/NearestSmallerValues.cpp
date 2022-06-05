#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<pair<int, int>> has;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    auto it = lower_bound(has.begin(), has.end(), pair<int, int>({x, 0}));
    if (it == has.begin()) cout << 0 << ' ';
    else cout << (*--it).second + 1 << ' ';
    while (has.size() && has.back().first >= x) has.pop_back();
    has.push_back({x, i});
  }
  cout << '\n';
  return 0;
}
