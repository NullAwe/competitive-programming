#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll sum = 0, m = 0; for (ll num : arr) sum += num, m = max(m, num);
  cout << max(sum, m * 2) << '\n';
  return 0;
}
