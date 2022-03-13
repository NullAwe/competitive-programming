#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  ll sum = 0; for (int num : arr) sum += num;
  if (n % 2 == 0) sum -= arr[n / 2];
  ll sum2 = 0; for (int i = n / 2 + 1; i < n; ++i) sum2 += arr[i];
  cout << (sum2 * 2 > sum ? "YES\n" : "NO\n");
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
