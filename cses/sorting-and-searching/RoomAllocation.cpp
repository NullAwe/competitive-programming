#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<pii> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i].first >> arr[i].second;
  vector<int> nums; for (pii p : arr) nums.push_back(p.first), nums.push_back(p.second);
  sort(nums.begin(), nums.end());
  for (int i = 0; i < n; ++i) arr[i].first = lower_bound(nums.begin(), nums.end(), arr[i].first) - nums.begin(),
    arr[i].second = lower_bound(nums.begin(), nums.end(), arr[i].second) - nums.begin();
  map<pii, queue<int>> m; for (int i = 0; i < n; ++i) m[arr[i]].push(i);
  int id = nums.size();
  vector<int> end(id + 1), start(id + 1);
  vector<vector<int>> s(id + 1);
  for (pii p : arr) ++start[p.first], ++end[p.second + 1], s[p.second + 1].push_back(p.first);
  int t = 0, ans = 0;
  for (int i = 0; i <= id; ++i) t += start[i] - end[i], ans = max(ans, t);
  queue<int> av; for (int i = 1; i <= ans; ++i) av.push(i);
  vector<queue<int>> cur(id + 1);
  vector<int> rooms(n);
  for (int i = 0; i <= id; ++i) {
    for (int j = 0; j < end[i]; ++j) av.push(cur[s[i][j]].front()), rooms[m[{s[i][j], i - 1}].front()] = cur[s[i][j]].front(),
      cur[s[i][j]].pop(), m[{s[i][j], i - 1}].pop();
    for (int j = 0; j < start[i]; ++j) cur[i].push(av.front()), av.pop();
  }
  cout << ans << '\n';
  for (int room : rooms) cout << room << ' ';
  cout << '\n';
  return 0;
}
