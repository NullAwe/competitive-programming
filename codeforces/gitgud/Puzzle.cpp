#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_N = 200000;

int n;
vector<int> a0(MAX_N), a1(MAX_N), b0(MAX_N), b1(MAX_N);

ll dp(int i) {
  if (i >= n) return 0;
  if (a0[i] + a1[i] < b0[i] + b1[i]) swap(a0, b0), swap(a1, b1);
  ll ans = 0;
  int one = 0, two = 0;
  for (; i < n; ++i) {
    one += a0[i], two += a1[i];
    a0[i] = a1[i] = 0;
    if (b0[i] && one) --one, b0[i] = 0;
    if (b1[i] && two) --two, b1[i] = 0;
    if (b0[i] && two) --two, ++ans, b0[i] = 0;
    if (b1[i] && one) --one, ++ans, b1[i] = 0;
    if (b0[i] || b1[i]) return ans + dp(i);
    ans += one + two;
  }
  return ans;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a0[i];
  for (int i = 0; i < n; ++i) cin >> a1[i];
  for (int i = 0; i < n; ++i) cin >> b0[i];
  for (int i = 0; i < n; ++i) cin >> b1[i];
  int ones = 0; for (int i = 0; i < n; ++i) ones += a0[i] + a1[i] - b0[i] - b1[i];
  if (ones) {
    cout << -1 << '\n';
    return 0;
  }
  cout << dp(0) << '\n';
  return 0;
}
