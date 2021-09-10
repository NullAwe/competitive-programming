#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  map<int, int> m;
  for (int i = 0; i < n; ++i) m[arr[i]] = i;
  int ans = 1;
  for (int i = 2; i <= n; ++i) if (m[i - 1] > m[i]) ++ans;
  // Output:
  cout << ans << endl;
  return 0;
}
