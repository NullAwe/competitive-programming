#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) --arr[i];
  vector<int> ans(n, -1);
  for (int i = 0; i < n; ++i) {
    if (ans[i] >= 0) continue;
    vector<int> p; int cur;
    for (cur = i; ans[cur] == -1; p.push_back(cur), ans[cur] = 0, cur = arr[cur]);
    if (!ans[cur]) {
      vector<int> group;
      while (p.back() != cur) group.push_back(p.back()), p.pop_back();
      group.push_back(p.back()), p.pop_back();
      for (int num : group) ans[num] = group.size();
    }
    while (p.size()) ans[p.back()] = ans[arr[p.back()]] + 1, p.pop_back();
  }
  for (int num : ans) cout << num << ' ';
  cout << '\n';
  return 0;
}
