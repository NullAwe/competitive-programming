#include <bits/stdc++.h>
using namespace std;

int pow10(int exp) {
  int base = 1;
  for (int i = 0; i < exp; ++i) base *= 10;
  return base;
}

void solve() {
  int s, n; cin >> s >> n;
  while (n > 1) {
    // Takes away the largest power of 10 that we can:
    string str = to_string(s);
    int largest = str.size() - 1;
    while (s - pow10(largest) < n - 1) --largest;
    s -= pow10(largest);
    --n;
    // Output:
    cout << pow10(largest) << " ";
  }
  // Final output:
  cout << s << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}