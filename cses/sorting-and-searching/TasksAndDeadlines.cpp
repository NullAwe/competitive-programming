#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

int main() {
  int n; cin >> n;
  vector<pii> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i].first >> arr[i].second;
  sort(arr.begin(), arr.end());
  ll ans = 0, time = 0;
  for (int i = 0; i < n; ++i) {
    time += arr[i].first;
    ans += arr[i].second - time;
  }
  cout << ans << '\n';
  return 0;
}
