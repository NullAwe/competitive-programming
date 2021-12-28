#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int lo = 0, hi = 1e9 + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    vector<ll> copy = arr;
    bool works = true;
    for (int i = n - 1; i >= 2; --i) {
      if (copy[i] < mid) {
        works = false;
        break;
      }
      int takeaway = min(copy[i] - mid, arr[i]) / 3;
      copy[i - 1] += takeaway, copy[i - 2] += takeaway * 2;
    }
    if (copy[0] < mid || copy[1] < mid || !works) hi = mid;
    else lo = mid;
  }
  // Output:
  cout << lo << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
