#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
int main() {
  int n;
  cin >> n;
  vector<ll> ans(n + 1);
  ans[0] = 1;
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < 7; ++j) {
      int get = i - j;
      if (get < 0) break;
      ans[i] += ans[get];
    }
    ans[i] %= 1000000007;
  }
  cout << ans[n] << "\n";
  return 0;
}
