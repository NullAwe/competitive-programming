#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

#define ll long long

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

int main() {
  int n, x; cin >> n >> x;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  if (n == 1) {
    cout << (arr[0] == x ? 1 : 0) << '\n';
    return 0;
  }
  int a = n / 2, b = n - a;
  gp_hash_table<ll, int, custom_hash> sums;
  for (int i = 0; i < (1 << a); ++i) {
    ll sum = 0;
    for (int j = 0; j < a; ++j) if (i & (1 << j)) sum += arr[j];
    ++sums[sum];
  }
  ll ans = 0;
  for (int i = 0; i < (1 << b); ++i) {
    ll sum = 0;
	for (int j = 0; j < b; ++j) if (i & (1 << j)) sum += arr[j + a];
    if (sum <= x) ans += sums[x - sum];
  }
  cout << ans << '\n';
  return 0;
}
