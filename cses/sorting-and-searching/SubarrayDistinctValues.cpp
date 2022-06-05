#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, k; cin >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  map<int, int> m; int count = 0, ind = 0;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    if (i && !--m[arr[i - 1]]) --count;
    while (ind < n) {
      if (count == k && !m[arr[ind]]) break;
      if (!m[arr[ind]]) ++count;
      ++m[arr[ind]], ++ind;
    }
    ans += ind - i;
  }
  cout << ans << '\n';
  return 0;
}
