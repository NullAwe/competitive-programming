#include <bits/stdc++.h>
using namespace std;

void solve(vector<int>& xors) {
  int a, b; cin >> a >> b;
  // Output:
  if (xors[a - 1] == b) cout << a << endl;
  else if ((xors[a - 1] ^ b) != a) cout << a + 1 << endl;
  else cout << a + 2 << endl;
}

int main() {
  int t; cin >> t;
  vector<int> xors(300001);
  for (int i = 1; i < xors.size(); ++i) xors[i] = xors[i - 1] ^ i;
  for (int i = 0; i < t; ++i) solve(xors);
  return 0;
}