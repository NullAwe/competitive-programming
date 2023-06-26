#include <bits/stdc++.h>
using namespace std;

const int MX_SUM = 180001;

int qry(int x) {
  cout << x << endl;
  int res; cin >> res;
  if (res <= 0) exit(0);
  return res;
}

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<bool>> dp(n + 1, vector<bool>(MX_SUM));
  dp[0][MX_SUM / 2] = true;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < MX_SUM; ++j) {
      int t1 = j - arr[i], t2 = j + arr[i];
      if (t1 >= 0 && dp[i][t1]) dp[i + 1][j] = true;
      else if (t2 < MX_SUM && dp[i][t2]) dp[i + 1][j] = true;
    }
  }
  if (!dp[n][MX_SUM / 2]) {
    cout << "First" << endl;
    while (true) {
      int i;
      for (i = 0; i < n; ++i) if (arr[i]) break;
      int j = qry(i + 1) - 1;
      int mn = min(arr[i], arr[j]);
      arr[i] -= mn, arr[j] -= mn;
    }
  } else {
    vector<bool> pos(n);
    int cur = MX_SUM / 2;
    for (int i = n - 1; i >= 0; --i) {
      int t1 = cur - arr[i], t2 = cur + arr[i];
      if (t1 >= 0 && dp[i][t1]) pos[i] = true, cur = t1;
      else cur = t2;
    }
    cout << "Second" << endl;
    vector<bool> playable(n, true);
    int start; cin >> start; --start;
    while (true) {
      int i;
      for (i = 0; i < n; ++i) if (playable[i] && pos[i] ^ pos[start]) break;
      int mn = min(arr[i], arr[start]);
      if (arr[i] == mn) playable[i] = false;
      if (arr[start] == mn) playable[start] = false;
      arr[i] -= mn, arr[start] -= mn;
      start = qry(i + 1) - 1;
    }
  }
  return 0;
}