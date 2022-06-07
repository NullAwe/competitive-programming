#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll f(string num) {
  if (num[0] == '-') return 0;
  if (num == "0") return 1;
  vector<ll> dp(19); dp[0] = 1;
  for (int i = 1; i < 18; ++i) dp[i] = dp[i - 1] * 9;
  ll ans = 0;
  for (int z = 1; z < num.size(); z += 2) ans += 10 * dp[num.size() - z - 1];
  if (num.size() & 1) ++ans;
  ans += (num[0] - '0' - 1) * dp[num.size() - 1];
  for (int i = 1; i < num.size(); ++i) {
    int mult = num[i] - '0';
    if (num[i - 1] < num[i]) --mult;
    ans += mult * dp[num.size() - i - 1];
    if (num[i - 1] == num[i]) break;
    if (i == num.size() - 1) ++ans;
  }
  return ans;
}

int main() {
  ll a, b; cin >> a >> b;
  cout << f(to_string(b)) - f(to_string(a - 1)) << '\n';
  return 0;
}
