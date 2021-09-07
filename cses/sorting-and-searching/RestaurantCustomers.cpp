#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  // Stores the endpoints of the intervals:
  vector<int> b(n), e(n);
  for (int i = 0; i < n; ++i) cin >> b[i] >> e[i];
  sort(b.begin(), b.end());
  sort(e.begin(), e.end());
  // Calculates the answer by iterating through the endpoints:
  int i = 0, j = 0, ans = 0, count = 0;
  while (i < n || j < n) {
	int m = INT_MAX;
	if (i < n) m = min(m, b[i]);
	if (j < n) m = min(m, e[j]);
	while (i < n && b[i] == m) {
	  ++count;
	  ++i;
	}
	while (j < n && e[j] == m) {
	  --count;
	  ++j;
	}
	ans = max(ans, count);
  }
  // Output:
  cout << ans << endl;
  return 0;
}
