#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  double ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double m = min(arr[i], arr[j]);
      ans += m * m / arr[i] / arr[j] * (1 - 1.0 / m) / 2;
      if (arr[i] > arr[j]) ans += (arr[i] - m) / arr[i];
    }
  }
  cout << fixed << setprecision(6) << ans << '\n';
  return 0;
}

