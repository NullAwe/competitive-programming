#include <iostream>
using namespace std;

#define ll long long

ll p(int x, int y) {
  ll ans = 1;
  for (int i = 0; i < y; ++i) ans *= x;
  return ans;
}

int main() {
  int n; cin >> n;
  cout << 6 * p(4, n - 2) + (n - 3) * 9 * p(4, n - 3) << '\n';
  return 0;
}
