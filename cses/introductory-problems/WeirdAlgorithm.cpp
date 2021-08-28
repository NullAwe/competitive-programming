#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  ll n; cin >> n;
  // Simulates:
  while (n != 1) {
    cout << n << " ";
    if (n % 2 == 0) n >>= 1;
    else n = 3 * n + 1;
  }
  // Final output:
  cout << 1 << endl;
  return 0;
}
