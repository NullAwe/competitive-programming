#include <bits/stdc++.h>
using namespace std;

const int MAX_A = 200001;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> count(MAX_A); for (int num : arr) ++count[num];
  vector<int> store(MAX_A);
  vector<vector<int>> divs(MAX_A);
  for (int i = 2; i < MAX_A; ++i) store[i] = count[i];
  for (int i = 2; i < MAX_A; ++i) for (int j = i + i; j < MAX_A; j += i)
    store[i] += count[j], divs[j].push_back(i);
  for (int i = 0; i < MAX_A; ++i) reverse(divs[i].begin(), divs[i].end());
  vector<vector<bool>> dp(MAX_A, vector<bool>(2));
  dp[1][0] = dp[1][1] = true;
  vector<int> minus(MAX_A);
  for (int i = 2; i < MAX_A; ++i) {
    for (int div : divs[i]) minus[div] = store[i];
    for (int div : divs[i]) {
      if (store[div] > minus[div]) {
        int left = store[div] - store[i];
        if (!dp[div][left & 1]) dp[i][1] = true;
        --left;
        if (!dp[div][left & 1]) dp[i][0] = true;
        for (int _div : divs[div]) minus[_div] += store[div] - minus[div];
      }
    }
    if (!dp[i][0] && !dp[i][1]) dp[i][1] = true;
  }
  for (int start : arr) {
    int left = store[start] - 1;
    bool win = false;
    if (dp[start][left & 1]) cout << "Aoki\n";
    else cout << "Takahashi\n";
  }
  return 0;
}