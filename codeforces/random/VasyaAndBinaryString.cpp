#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  string str; cin >> str;
  vector<ll> vals(n); for (int i = 0; i < n; ++i) cin >> vals[i];
  vector<vector<vector<ll>>> memo(n, vector<vector<ll>>(n, vector<ll>(n + 1)));
  for (int i = 0; i < n; ++i) for (int j = 1; j <= n; ++j) memo[i][i][j] = vals[j - 1];
  for (int len = 2; len <= n; ++len) {
    for (int start = 0; start + len <= n; ++start) {
      int end = start + len - 1;
      for (int i = 1; i <= n; ++i) {
        memo[start][end][i] = vals[i - 1] + memo[start + 1][end][1];
        for (int k = start + 1; k <= end; ++k) if (str[start] == str[k])
          memo[start][end][i] = max(memo[start][end][i], memo[start + 1][k - 1][1] + memo[k][end][i + 1]);
      }
    }
  }
  // Output:
  cout << memo[0][n - 1][1] << endl;
  return 0;
}
