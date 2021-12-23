#include <bits/stdc++.h>
using namespace std;

bool check(vector<int>& arr, int l, int r) {
  if (l >= r) return true;
  if ((r - l) % 2 == 1) return false;
  int second = -1;
  for (int i = l + 1; i < r; ++i) {
    if (i < 0 || i >= arr.size()) return false;
    if (arr[i] == arr[l]) {
      second = i;
      break;
    }
  }
  if (second < 0) return false;
  return check(arr, l + 1, second) && check(arr, second + 1, r);
}

bool isSub(vector<int>& a, vector<int>& b) {
  if (a.size() > b.size()) return false;
  int ind = 0, lastCheck = -1;
  for (int i = 0; i < b.size(); ++i) {
    if (ind >= a.size()) continue;
    if (b[i] == a[ind]) {
      ++ind;
      if (!check(b, lastCheck + 1, i)) return false;
      lastCheck = i;
    }
  }
  if (!check(b, lastCheck + 1, b.size())) return false;
  return ind == a.size();
}

void solve() {
  int n, m; cin >> n >> m;
  set<int> cannot;
  vector<int> last;
  bool ans = true;
  for (int i = 0; i < m; ++i) {
    int k; cin >> k;
    vector<int> now(k); for (int j = 0; j < k; ++j) cin >> now[j];
    if (!ans) continue;
    set<int> has; for (int num : now) has.insert(num);
    vector<int> newLast;
    for (int num : last) {
      if (has.count(num)) newLast.push_back(num);
      else cannot.insert(num);
    }
    if (!isSub(newLast, now)) ans = false;
    for (int num : now) if (cannot.count(num)) ans = false;
    last = now;
  }
  // Output:
  cout << (ans ? "YES" : "NO") << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
