#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> nums(1000001);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    ++nums[x];
  }
  int ans = 1;
  for (int i = 2; i < 1000001; ++i) {
    int count = 0;
    for (int j = i; j < 1000001; j += i) count += nums[j];
    if (count > 1) ans = i;
  }
  cout << ans << '\n';
  return 0;
}
