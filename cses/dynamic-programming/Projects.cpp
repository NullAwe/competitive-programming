#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

int main() {
  int n; cin >> n;
  vector<pair<pii, ll>> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i].first.second >> arr[i].first.first >> arr[i].second;
  sort(arr.begin(), arr.end());
  vector<int> ends; ends.push_back(0);
  for (int i = 0; i < n; ++i) if (ends.back() < arr[i].first.first) ends.push_back(arr[i].first.first);
  vector<ll> dp(ends.size());
  for (pair<pii, ll> p : arr) {
    int start = p.first.second, end = p.first.first; ll gain = p.second;
    int si = lower_bound(ends.begin(), ends.end(), start) - ends.begin() - 1,
        ei = lower_bound(ends.begin(), ends.end(), end) - ends.begin();
    dp[ei] = max(dp[ei], max(dp[ei - 1], dp[si] + gain));
  }
  cout << dp[ends.size() - 1] << '\n';
  return 0;
}
