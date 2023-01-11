#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> arr, b;
vector<vector<int>> at;
vector<bool> done;
set<int> s;

bool dfs(int v) {
  if (s.count(b[v])) return false;
  if (done[b[v]]) return true;
  done[b[v]] = true;
  s.insert(b[v]);
  for (int num : at[b[v]]) {
    if (!dfs(num)) return false;
  }
  s.erase(b[v]);
  return true;
}

void solve() {
  arr.clear(), b.clear(), at.clear(), done.clear(), s.clear();
  int n; cin >> n;
  arr.resize(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  b.resize(n); for (int i = 0; i < n; ++i) cin >> b[i];
  for (int i = 0; i < n; ++i) --arr[i], --b[i];
  if (n == 1) {
    cout << "AC\n";
    return;
  }
  vector<int> count(n);
  for (int num : arr) ++count[num];
  int mx = 0;
  for (int num : count) mx = max(mx, num);
  int ind;
  for (ind = 0; ind < n; ++ind) if (count[ind] == mx) break;
  vector<bool> cancelled(n);
  for (int i = 0; i < n; ++i) cancelled[i] = (arr[i] == ind || b[i] == ind);
  at.resize(n);
  for (int i = 0; i < n; ++i) {
    if (cancelled[i]) continue;
    at[arr[i]].push_back(i);
  }
  done.resize(n);
  for (int i = 0; i < n; ++i) {
    if (done[b[i]]) continue;
    if (!dfs(i)) {
      cout << "WA\n";
      return;
    }
  }
  cout << "AC\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}