#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll dp(int ind, int doors, vector<int>& arr, vector<vector<vector<ll>>>& memo, int orig) {
  if (ind >= orig + arr.size()) return 0;
  if (doors == 0) return LLONG_MAX;
  if (memo[orig][ind % arr.size()][doors] < LLONG_MAX) return memo[orig][ind % arr.size()][doors];
  ll sum = 0;
  for (int i = ind; i < orig + arr.size(); ++i) {
    sum += arr[i % arr.size()] * (i - ind);
    ll next = dp(i + 1, doors - 1, arr, memo, orig);
    if (next < LLONG_MAX) memo[orig][ind % arr.size()][doors] = min(memo[orig][ind % arr.size()][doors], sum + next);
  }
  return memo[orig][ind % arr.size()][doors];
}

int main() {
  ifstream in("cbarn2.in");
  ofstream out("cbarn2.out");
  int n, k; in >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) in >> arr[i];
  vector<vector<vector<ll>>> memo(n, vector<vector<ll>>(n, vector<ll>(k + 1, LLONG_MAX)));
  ll ans = LLONG_MAX;
  for (int i = 0; i < n; ++i) ans = min(ans, dp(i, k, arr, memo, i));
  // Output:
  out << ans << endl;
  return 0;
}
