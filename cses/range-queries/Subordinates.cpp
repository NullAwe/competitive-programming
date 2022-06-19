#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 1; i < n; ++i) cin >> arr[i];
  for (int i = 1; i < n; ++i) --arr[i];
  vector<int> in(n); for (int i = 1; i < n; ++i) ++in[arr[i]];
  queue<int> q; for (int i = 0; i < n; ++i) if (!in[i]) q.push(i);
  vector<int> ans(n);
  while (q.size()) {
    int node = q.front(); q.pop();
    ans[arr[node]] += ans[node] + 1;
    --in[arr[node]];
    if (!in[arr[node]] && arr[node]) q.push(arr[node]);
  }
  for (int num : ans) cout << num << ' ';
  cout << '\n';
  return 0;
}
