#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, x; cin >> n >> x;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  map<int, int> m;
  for (int i = 0; i < n; ++i) {
    if (m[x - arr[i]]) {
      // Output:
      cout << m[x - arr[i]] << " " << i + 1 << endl;
      return 0;
    }
    m[arr[i]] = i + 1;
  }
  // Output:
  cout << "IMPOSSIBLE" << endl;
  return 0;
}
