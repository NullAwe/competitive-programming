#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
  for (int i = 2; i * i <= n; ++i) if (n % i == 0) return false;
  return true;
}

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int sum = 0;
  for (int num : arr) sum += num;
  if (!isPrime(sum)) {
    // Output:
    cout << n << endl;
    for (int i = 1; i <= n; ++i) cout << i << ' ';
    cout << endl;
    return;
  }
  for (int i = 0; i < n; ++i) {
    if (!isPrime(sum - arr[i])) {
      // Output:
      cout << n - 1 << endl;
      for (int j = 1; j <= n; ++j) if (j - 1 != i) cout << j << ' ';
      cout << endl;
      return;
    }
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
