#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200;

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n, k; cin >> n >> k;
    vector<int> count(MAX_N);
    for (int j = 0; j < n; ++j) { int x; cin >> x; ++count[x]; }
    int a = 0, b = 0;
    bool can = true;
    for (int j = 0; j < MAX_N; ++j) {
      if (count[j] > 2) can = false;
      else if (count[j] == 2) ++b;
      else if (count[j] == 1) ++a;
    }
    if ((a + 1) / 2 + b > k) can = false;
    cout << "Case #" << i << ": " << (can ? "YES" : "NO") << '\n';
  }
  return 0;
}
