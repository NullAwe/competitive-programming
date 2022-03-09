#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_N = 100001;

void solve() {
  int n, m; cin >> n >> m;
  int rn = n, rm = m;
  if (n < m) swap(rn, rm);
  int arr[rn][rm];
  if (n < m) for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> arr[j][i];
  else for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> arr[i][j];
  n = rn, m = rm;
  int colors[MAX_N][m]; for (int i = 0; i < MAX_N; ++i) for (int j = 0; j < m; ++j) colors[i][j] = 0;
  ll sums[MAX_N]; int nums[MAX_N], last[MAX_N]; for (int i = 0; i < MAX_N; ++i) sums[i] = nums[i] = last[i] = 0;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int color = arr[i][j];
      if (nums[color] == 0) {
        nums[color] = 1;
        colors[color][j] = 1;
        last[color] = i;
        continue;
      }
      sums[color] += (ll) (i - last[color]) * nums[color];
      ++nums[color];
      ++colors[color][j];
      last[color] = i;
      ans += sums[color];
      for (int k = 0; k < m; ++k) ans += (ll) abs(k - j) * colors[color][k];
    }
  }
  cout << ans << '\n';
}

int main() {
  solve();
  return 0;
}
