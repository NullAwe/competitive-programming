#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline ll msb(ll x) {
  ll ans = 1;
  while ((ans << 1) <= x) ans <<= 1;
  return ans;
}

void solve() {
  int n; cin >> n;
  vector<ll> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<ll> xors(n);
  for (int i = 0; i < n; ++i) xors[0] ^= arr[i];
  vector<ll> rb(n), re(n);
  if (xors[0] == 0) rb[0] = re[n - 1] = -1;
  else rb[0] = re[n - 1] = msb(xors[0]);
  for (int len = n; len > 1; --len) {
    for (int i = 0; i + len <= n; ++i) {
      int j = i + len - 1;
      if (((rb[i] | re[j]) & xors[i]) || rb[i] < 0 || re[j] < 0) {
        if (xors[i] == 0) rb[i] = re[j] = -1;
        else rb[i] |= msb(xors[i]), re[j] |= msb(xors[i]);
      }
    }
    for (int start = n - len + 1; start > 0; --start) xors[start] = xors[start - 1] ^ arr[start - 1];
    xors[0] ^= arr[len - 1];
  }
  for (int i = 0; i < n; ++i) {
    if (((rb[i] | re[i]) & xors[i]) || rb[i] < 0 || re[i] < 0) cout << 1;
    else cout << 0;
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}