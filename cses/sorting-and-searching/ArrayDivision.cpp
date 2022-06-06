#include <bits/stdc++.h>
using namespace std;

#define ll long long

int k;
vector<int> arr;

bool check(ll val) {
  ll sum = 0, buckets = 0;
  for (int num : arr) {
    if (num > val) return false;
    if (sum + num > val) ++buckets, sum = num;
    else sum += num;
  }
  return buckets < k;
}

int main() {
  int n; cin >> n >> k;
  arr = vector<int>(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll lo = 0, hi = 1e18;
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    if (check(mid)) hi = mid;
    else lo = mid;
  }
  cout << hi << '\n';
  return 0;
}
