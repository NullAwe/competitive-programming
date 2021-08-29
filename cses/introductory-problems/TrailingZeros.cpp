#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  int ans = 0;
  for (int i = 5; i <= n; i += 5) {
    int tmp = i;
    while (tmp % 5 == 0) {
      ++ans;
      tmp /= 5;
    }
  }
  // Output:
  cout << ans << endl;
  return 0;
}
