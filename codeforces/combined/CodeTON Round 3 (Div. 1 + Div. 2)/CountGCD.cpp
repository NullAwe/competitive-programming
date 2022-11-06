#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

void solve() {
  int n, m; cin >> n >> m;
  vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  ll last = 1, tmp = a[0];
  vector<int> pf;
  for (int i = 2; i * i <= tmp; ++i) while (tmp % i == 0) pf.push_back(i), tmp /= i;
  if (tmp > 1) pf.push_back(tmp);
  for (int iter = 1; iter < n; ++iter) {
    if (a[iter - 1] % a[iter]) {
      cout << "0\n";
      return;
    }
    vector<int> npf;
    tmp = a[iter];
    for (int num : pf) if (tmp % num == 0) npf.push_back(num), tmp /= num;
    vector<int> nums;
    int i = 0, ind = 0;
    while (i < pf.size()) {
      int cur = pf[i], start = i;
      while (i < pf.size() && pf[i] == cur) ++i;
      int cur2 = ind == npf.size() ? 2 * MOD : npf[ind], start2 = ind;
      if (cur != cur2) {
        nums.push_back(cur);
        continue;
      }
      while (ind < npf.size() && npf[ind] == cur) ++ind;
      if (ind - start2 < i - start) nums.push_back(cur);
    }
    ll mx = m / a[iter], sum = mx;
    for (int i = 1; i < (1 << nums.size()); ++i) {
      int sign = __builtin_popcount(i) & 1, mult = 1;
      for (int j = 0; j < nums.size(); ++j) if (i & (1 << j)) mult *= nums[j];
      sum += -(sign * 2 - 1) * (mx / mult);
    }
    last = last * sum % MOD, pf = npf;
  }
  cout << last << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
