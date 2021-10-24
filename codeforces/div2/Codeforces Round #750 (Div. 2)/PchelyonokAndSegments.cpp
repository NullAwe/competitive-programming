#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_N = 500;

void solve() {
  int n; cin >> n;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Stores prefix sums for fast subarray sum calculation:
  vector<ll> pref(n + 1); for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + arr[i];
  // Finds answer using dynamic programming:
  vector<vector<ll>> memo(n + 1, vector<ll>(MAX_N));
  for (int i = 1; i < MAX_N; ++i) memo[n][i] = -1;
  for (int i = 0; i <= n; ++i) memo[i][0] = INT_MAX;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 1; j < MAX_N; ++j) {
      memo[i][j] = memo[i + 1][j];
      if (i + j - 1 < n) {
        ll sum = pref[i + j] - pref[i];
        if (sum < memo[i + j][j - 1]) memo[i][j] = max(memo[i][j], sum);
      }
    }
  }
  for (int i = MAX_N - 1; i >= 0; --i) {
    if (memo[0][i] >= 0) {
      // Output:
      cout << i << endl;
      return;
    }
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}