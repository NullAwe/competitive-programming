#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  // Output:
  if (k < 2 || k > 3 || n < 4 || (n == 4 && k == 2)) cout << -1 << endl;
  else {
    cout << n - 1 << endl;
    if (k == 2) for (int i = 1; i < n; ++i) cout << i << ' ' << i + 1 << endl;
    else for (int i = 1; i < n; ++i) cout << (i <= n / 2 ? n : 1) << ' ' << i << endl;
  }
  return 0;
}
