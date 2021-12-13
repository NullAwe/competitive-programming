#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int twos = 0;
  for (int i = 0; i < n; ++i) {
    while (arr[i] % 2 == 0) {
      ++twos;
      arr[i] >>= 1;
    }
  }
  int maxInd = 0;
  for (int i = 0; i < n; ++i) if (arr[i] > arr[maxInd]) maxInd = i;
  for (int i = 0; i < twos; ++i) arr[maxInd] *= 2;
  ll sum = 0;
  for (ll num : arr) sum += num;
  // Output:
  cout << sum << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
