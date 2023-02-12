#include <bits/stdc++.h>
using namespace std;

void solve(int n, int k, int add) {
  if (3 * k >= n) {
    for (int i = k + 1; i <= n; ++i) cout << i + add << ' ';
    for (int i = 1; i <= k; ++i) cout << i + add << ' ';
    cout << '\n';
    return;
  } else if (k > n / 4) {
    for (int i = k + 1; i <= 2 * k; ++i) cout << i + add << ' ';
    int end = n - 3 * k;
    for (int i = 1; i <= end; ++i) cout << i + add << ' ';
    for (int i = 2 * k + end + 1; i <= n; ++i) cout << i + add << ' ';
    for (int i = end + 1; i <= k; ++i) cout << i + add << ' ';
    for (int i = 1; i <= end; ++i) cout << i + 2 * k + add << ' ';
    cout << '\n';
    return;
  }
  for (int i = k + 1; i <= 2 * k; ++i) cout << i + add << ' ';
  for (int i = 1; i <= k; ++i) cout << i + add << ' ';
  solve(n - 2 * k, k, add + 2 * k);
}

int main() {
  int n, k; cin >> n >> k;
  if (k > n / 2) {
    cout << -1 << '\n';
    return 0;
  }
  solve(n, k, 0);
  return 0;
}