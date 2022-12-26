#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAX_N = 5000;

inline int add(int a, int b) { return a + b < MOD ? a + b : a + b - MOD; }

inline int sub(int a, int b) { return add(a, MOD - b); }

inline int mult(int a, int b) { return (long long) a * b % MOD; }

vector<vector<int>> dp(MAX_N, vector<int>(MAX_N)), ps(MAX_N, vector<int>(MAX_N + 1));
int ans = 0;

void solve(int n, int m, bool minus) {
  for (int i = 1; i < MAX_N; ++i) for (int x = 1; x < n; ++x) {
    int val = mult(dp[x][i], dp[n - x + 1][i - 1]);
    ps[x + 1][i - 1] = add(ps[x][i - 1], val);
  }
  for (int i = 0; i < m - 1; ++i) for (int j = 1; j < n; ++j) {
    int l = i + 1, r = m - i - 1;
    int lh = j + 1, rh = n - j - 1;
    int lw = mult(dp[lh][l - 1], dp[rh + 1][l]);
    int rw = ps[lh - minus][r - 1];
    ans = add(ans, mult(lw, rw));
  }
}

int main() {
  dp[0][0] = 1;
  vector<int> p(MAX_N + 1, 1); p[0] = 0;
  ps[0] = vector<int>(MAX_N + 1, 1); ps[0][0] = 0;
  for (int i = 1; i < MAX_N; ++i) for (int j = 0; j < MAX_N; ++j)
    dp[i][j] = p[j + 1], p[j + 1] = add(p[j], dp[i][j]);
  int n, m; cin >> n >> m;
  solve(n, m, false);
  solve(m, n, true);
  cout << mult(2, ans) << '\n';
  return 0;
}