#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<int> primes;

int rp(int n, int m) {
  int ans = 0, sz = primes.size();
  // Finds the number of integers coprime to n less than m using PIE:
  for (int i = 0; i < (1 << sz); ++i) {
    int mult = 1, sign = pow(-1, __builtin_popcount(i));
    for (int j = 0; j < sz; ++j) {
      if (i & (1 << j)) mult *= primes[j];
    }
    ans += (m / mult) * sign;
  }
  return ans;
}

void solve() {
  int x, p, k; cin >> x >> p >> k;
  primes.resize(0);
  int tmp = p;
  for (int i = 2; i * i <= tmp; ++i) {
    if (tmp % i == 0) primes.push_back(i);
    while (tmp % i == 0) tmp /= i;
  }
  if (tmp > 1) primes.push_back(tmp);
  int rpx = rp(p, x);
  // Binary searches for the answer:
  int lo = x, hi = 10000000;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2, place = rp(p, mid) - rpx;
    if (place >= k) hi = mid;
    else lo = mid;
  }
  // Output:
  cout << hi << endl;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
