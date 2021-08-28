#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  int ans = 1;
  // Finds answer using non-efficient exponentiation because I'm too lazy to implement efficient exponentiation:
  for (int i = 0; i < n; ++i) ans = (ans << 1) % 1000000007;
  // Output:
  cout << ans << endl;
  return 0;
}
