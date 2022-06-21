#include <iostream>
using namespace std;

int solve(int n, int k, bool first) {
  if (n == 1) return 1;
  if (first && k <= (n + 1) / 2) return k * 2 - 1;
  if (k <= n / 2) return k * 2;
  if (first) return solve(n / 2, k - (n + 1) / 2, first ^ (n & 1)) * 2;
  return solve((n + 1) / 2, k - n / 2, first ^ (n & 1)) * 2 - 1;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) { int n, k; cin >> n >> k; cout << solve(n, k, 0) << '\n'; }
  return 0;
}

