#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  ll negSum = 0, posSum = 0;
  for (int num : arr) {
    if (num < 0) negSum -= num;
    else if (num > 0) posSum += num;
  }
  // Takes care of the edge case where the sum of the whole array is 0:
  if (negSum == posSum) {
    cout << "NO" << endl;
    return;
  }
  // Output:
  cout << "YES" << endl;
  if (negSum > posSum) for (int num : arr) cout << num << ' ';
  else for (int i = n - 1; i >= 0; --i) cout << arr[i] << ' ';
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
