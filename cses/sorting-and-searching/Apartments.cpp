#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m, k; cin >> n >> m >> k;
  vector<int> apt(n), ppl(m);
  for (int i = 0; i < n; ++i) cin >> apt[i];
  for (int i = 0; i < m; ++i) cin >> ppl[i];
  sort(apt.begin(), apt.end());
  sort(ppl.begin(), ppl.end());
  int i = 0, j = 0, ans = 0;
  while (i < n && j < m) {
	  if (apt[i] < ppl[j] - k) ++i;
  	else if (apt[i] > ppl[j] + k) ++j;
  	else ++i, ++j, ++ans;
  }
  // Output:
  cout << ans << endl;
  return 0;
}
