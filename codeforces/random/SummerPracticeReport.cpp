#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, k; cin >> n >> k;
  vector<int> t(n); for (int i = 0; i < n; ++i) cin >> t[i];
  vector<int> f(n); for (int i = 0; i < n; ++i) cin >> f[i];
  vector<int> dpt(n + 1, INT_MAX), dpf(n + 1, INT_MAX); dpt[0] = dpf[0] = 0;
  for (int i = 0; i <= n; ++i) {
    vector<ll> ht, hf;
    if (dpt[i] < INT_MAX) ht.push_back(k - dpt[i] + (ll) k * (f[i] - 1)), hf.push_back((ll) k * t[i]);
    if (dpf[i] < INT_MAX) ht.push_back((ll) k * f[i]), hf.push_back(k - dpf[i] + (ll) k * (t[i] - 1));
    for (int j = 0; j < ht.size(); ++j) {
      if (t[i] > ht[j]) {
        if (t[i] - ht[j] <= k) dpt[i + 1] = min(dpt[i + 1], t[i] - (int) ht[j]);
      } else if (hf[j] >= f[i]) dpt[i + 1] = 1;
      if (f[i] > hf[j]) {
        if (f[i] - hf[j] <= k) dpf[i + 1] = min(dpf[i + 1], f[i] - (int) hf[j]);
      } else if (ht[j] >= t[i]) dpf[i + 1] = 1;
    }
  }
  cout << (dpt[n] < INT_MAX || dpf[n] < INT_MAX ? "YES\n" : "NO\n");
  return 0;
}
