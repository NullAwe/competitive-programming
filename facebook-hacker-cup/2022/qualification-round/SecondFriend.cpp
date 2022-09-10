#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n, m; cin >> n >> m;
    vector<string> arr(n); for (int j = 0; j < n; ++j) cin >> arr[j];
    if (n > 1 && m > 1) {
      cout << "Case #" << i << ": Possible\n";
      for (int j = 0; j < n; ++j) cout << string(m, '^') << '\n';
      continue;
    }
    int ts = 0;
    for (int j = 0; j < n; ++j) for (int k = 0; k < m; ++k) ts += arr[j][k] == '^';
    if (ts) cout << "Case #" << i << ": Impossible\n";
    else {
      cout << "Case #" << i << ": Possible\n";
      for (string str : arr) cout << str << '\n';
    }
  }
  return 0;
}
