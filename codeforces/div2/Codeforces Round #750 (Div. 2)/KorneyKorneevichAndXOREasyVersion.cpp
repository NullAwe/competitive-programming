#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < arr.size(); ++i) cin >> arr[i];
  // Finds answer using dynamic programming:
  vector<int> memo(600, -1);
  memo[0] = INT_MAX;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < 600; ++j) {
      if (memo[j] <= arr[i]) continue;
      int val = j ^ arr[i];
      memo[val] = max(memo[val], arr[i]);
    }
  }
  vector<int> ans;
  for (int i = 0; i < 600; ++i) if (memo[i] != -1) ans.push_back(i);
  // Output:
  cout << ans.size() << endl;
  for (int num : ans) cout << num << ' ';
  cout << endl;
  return 0;
}