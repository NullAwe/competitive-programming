#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  string str; cin >> str;
  vector<vector<int>> prefix(k + 1, vector<int>(n + 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= k; ++j) prefix[j][i + 1] = prefix[j][i];
    ++prefix[str[i] == '?' ? k : str[i] - 'a'][i + 1];
  }
  int lo = 0, hi = n / k + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    vector<vector<int>> nearest(k, vector<int>(n + 1)); for (int i = n - mid + 1; i <= n; ++i) for (int j = 0; j < k; ++j) nearest[j][i] = INT_MAX;
    for (int i = n - mid; i >= 0; --i) {
      vector<int> fits;
      for (int j = 0; j < k; ++j)
        if (prefix[j][i + mid] + prefix[k][i + mid] - prefix[j][i] - prefix[k][i] == mid) 
          fits.push_back(j);
      for (int j = 0; j < k; ++j) nearest[j][i] = nearest[j][i + 1];
      for (int fit : fits) nearest[fit][i] = i;
    }
    vector<int> dp(1 << k, INT_MAX); dp[0] = 0;
    for (int i = 1; i < (1 << k); ++i) {
      for (int j = 0; j < k; ++j) {
        int last = i ^ (1 << j);
        if (last > i) continue;
        if (dp[last] == INT_MAX || nearest[j][dp[last]] == INT_MAX) continue;
        dp[i] = min(dp[i], nearest[j][dp[last]] + mid);
      }
    }
    if (dp[(1 << k) - 1] == INT_MAX) hi = mid;
    else lo = mid;
  }
  cout << lo << '\n';
  return 0;
}
