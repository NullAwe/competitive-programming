#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k, v; cin >> n >> k >> v;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Takes care of edge case where you just have to empty one tank:
  if (v == 0) {
    cout << "YES" << endl << "1000000000 1 2" << endl;
    return 0;
  }
  int sum = 0; for (int num : arr) sum += num;
  // Takes care of edge case where it's not possible:
  if (sum < v) {
    cout << "NO" << endl;
    return 0;
  }
  vector<vector<bool>> dp(n + 1, vector<bool>(k, false)); dp[0][0] = true;
  for (int i = 0; i < n; ++i) for (int j = 0; j < k; ++j)
    if (dp[i][j]) dp[i + 1][j] = dp[i + 1][(j + arr[i]) % k] = true;
  int ind = -1, val = v % k;
  for (int i = 1; i <= n; ++i) if (dp[i][v % k]) { ind = i; break; }
  // Takes care of when we can't find a sum:
  if (ind < 0) {
    cout << "NO" << endl;
    return 0;
  }
  cout << "YES" << endl;
  // Combine tanks to get the correct value when modded by k:
  set<int> include;
  for (int i = ind; i > 0; --i) for (int j = 0; j < k; ++j) {
    if (dp[i - 1][(val + k - (arr[i - 1] % k)) % k]) {
      val = (val + k - (arr[i - 1] % k)) % k;
      include.insert(i - 1);
      break;
    }
  }
  if (!include.size()) {
    cout << "1000000000 " << 1 << ' ' << 2 << endl;
    arr[1] += arr[0]; arr[0] = 0;
    include.insert(0);
  }
  int first = *include.begin(); include.erase(include.begin());
  for (int num : include) {
    cout << "1000000000 " << num + 1 << ' ' << first + 1 << endl;
    arr[first] += arr[num];
  }
  include.insert(first);
  // Combine all the other tanks:
  set<int> notInclude; for (int i = 0; i < n; ++i) if (!include.count(i)) notInclude.insert(i);
  int last = n - 1;
  if (notInclude.size()) {
    last = *notInclude.begin(); notInclude.erase(notInclude.begin());
    for (int num : notInclude) {
      cout << "1000000000 " << num + 1 << ' ' << last + 1 << endl;
      arr[last] += arr[num];
    }
  }
  // Fixes the answer by a multiple of k:
  if (arr[first] > v) cout << (arr[first] - v) / k << ' ' << first + 1 << ' ' << last + 1 << endl;
  else if (arr[first] < v) cout << (v - arr[first]) / k << ' ' << last + 1 << ' ' << first + 1 << endl; 
  return 0;
}
