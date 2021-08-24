#include <bits/stdc++.h>
using namespace std;

void solve() {
  int a, b; cin >> a >> b;
  vector<int> ans;
  vector<bool> done(a + b + 1);
  // Finds possible games broken with Alice serving (a + b) / 2 of the games:
  int s = (a + b) / 2, s2 = (a + b + 1) / 2;
  for (int i = 0; i < min(a, s) + 1; ++i) {
    int broken = s - i + a - i;
    if (a - i > s2) continue;
    if (!done[broken]) {
      ans.push_back(broken);
      done[broken] = true;
    }
  }
  // Finds possible games broken with Alice serving (a + b + 1) / 2 of the games:
  s = (a + b + 1) / 2, s2 = (a + b) / 2;
  for (int i = 0; i < min(a, s) + 1; ++i) {
    int broken = s - i + a - i;
    if (a - i > s2) continue;
    if (!done[broken]) {
      ans.push_back(broken);
      done[broken] = true;
    }
  }
  sort(ans.begin(), ans.end());
  // Output:
  cout << ans.size() << endl;
  for (int num : ans) cout << num << " ";
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
