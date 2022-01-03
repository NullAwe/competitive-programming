#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<vector<int>> cycles;
  vector<bool> done(n, false);
  for (int i = 0; i < n; ++i) {
    if (done[i]) continue;
    printf("? %d\n", i + 1); fflush(stdout);
    int res; scanf("%d", &res);
    vector<int> cycle; cycle.push_back(res);
    int ans = -1;
    while (ans != res) {
      printf("? %d\n", i + 1); fflush(stdout);
      scanf("%d", &ans); cycle.push_back(ans);
    }
    cycles.push_back(cycle);
    for (int num : cycle) done[num - 1] = true;
  }
  vector<int> ans(n);
  for (vector<int> cycle : cycles) for (int i = 1; i < cycle.size(); ++i) ans[cycle[i - 1] - 1] = cycle[i];
  // Output:
  cout << '!';
  for (int num : ans) cout << ' ' << num;
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
