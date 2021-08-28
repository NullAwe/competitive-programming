#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  // Stores which numbers have appeared:
  vector<bool> has(n);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    has[a - 1] = true;
  }
  for (int i = 0; i < n; ++i) {
    if (!has[i]) {
      // Output:
      cout << i + 1 << endl;
      return 0;
    }
  }
  return 0;
}
