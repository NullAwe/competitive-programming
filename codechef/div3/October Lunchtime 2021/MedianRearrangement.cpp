#include <bits/stdc++.h>
using namespace std;

#define ll long long

int works(ll ind, vector<ll>& arr, ll n, ll k) {
  if (ind < n / 2) return -1;
  if (ind > n / 2 * n) return 1;
  int avail = 0;
  ll sum = 0;
  for (int i = 0; i < n / 2 * n + n; ++i) {
    if (i >= ind && avail >= n / 2) {
      avail -= n / 2;
      sum += arr[i];
    } else ++avail;
  }
  if (sum > k) return 1;
  return 0;
}

void solve() {
  ll n, k; cin >> n >> k;
  vector<ll> arr(n * n); for (int i = 0; i < n * n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  ll lo = -1, hi = n * n;
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    int w = works(mid, arr, n, k);
    if (w <= 0) lo = mid;
    else hi = mid;
  }
  // Output:
  if (works(lo, arr, n, k) != 0 && works(hi, arr, n, k) != 0) cout << -1 << endl;
  else cout << arr[lo] << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}