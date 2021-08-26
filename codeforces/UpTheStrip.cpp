#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, m; cin >> n >> m;
  vector<int> memo((n + 1) / 2 + 1);
  memo[1] = 1;
  ll sum = 1;
  ll ans;
  for (int i = 2; i <= n; ++i) {
    ans = sum;
    int last = 1;
    for (int j = 2, k; j <= i; j = k) {
      int floored = i / j;
      int num = i / floored - last;
      ll newAns = (ll) num * memo[floored] + ans;
      ans = (int) (newAns % m);
      k = j + num;
      last = k - 1;
    }
    sum += ans;
    sum %= m;
    if (i < memo.size()) memo[i] = ans;
    cout << ans << endl;
  }
  cout << ans << endl;
  return 0;
}
