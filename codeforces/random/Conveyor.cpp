#include <iostream>
using namespace std;

#define ll long long

const int SZ = 120;

ll dp[SZ][SZ];

inline ll g(int a, int b) { return a < 0 || b < 0 ? 0 : dp[a][b]; }

void solve() {
  ll t; cin >> t;
  int a, b; cin >> a >> b;
  t -= a + b;
  if (t < 0) {
    cout << "NO\n";
    return;
  }
  dp[0][0] = t;
  for (int i = 0; i < SZ; ++i) for (int j = !i; j < SZ; ++j)
    dp[i][j] = (g(i - 1, j) / 2 + (g(i, j - 1) + 1) / 2);
  int x = 0, y = 0;
  while (x < SZ && y < SZ) {
    if (x == a && y == b) {
      cout << "YES\n";
      return;
    }
    if (dp[x][y] & 1) ++x;
    else ++y;
  }
  cout << "NO\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
