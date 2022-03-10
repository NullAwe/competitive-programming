#include <bits/stdc++.h>
using namespace std;

const vector<int> dx = {0, 0, -1, 1}, dy = {-1, 1, 0, 0};

int main() {
  int n; cin >> n;
  vector<pair<int, int>> points(n);
  map<pair<int, int>, int> checks;
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    points[i] = {a, b};
    checks[{a, b}] = i + 1;
  }
  queue<pair<int, int>> q;
  vector<pair<pair<int, int>, int>> ans(n);
  for (int i = 0; i < n; ++i) {
    int x = points[i].first, y = points[i].second;
    for (int j = 0; j < 4; ++j) {
      int nx = x + dx[j], ny = y + dy[j];
      if (checks[{nx, ny}]) continue;
      q.push({x, y});
      ans[i] = {{nx, ny}, 1};
      break;
    }
  }
  while (q.size()) {
    pair<int, int> point = q.front(); q.pop();
    int thisInd = checks[point] - 1;
    int x = point.first, y = point.second;
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i],  ny = y + dy[i];
      if (!checks[{nx, ny}]) continue;
      int ind = checks[{nx, ny}] - 1;
      if (ans[ind].second) continue;
      ans[ind] = {ans[thisInd].first, ans[thisInd].second + 1};
      q.push({nx, ny});
    }
  }
  for (int i = 0; i < n; ++i) cout << ans[i].first.first << ' ' << ans[i].first.second << '\n';
  return 0;
}
