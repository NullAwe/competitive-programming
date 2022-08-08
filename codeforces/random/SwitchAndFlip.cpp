#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void fix(vector<pii>& swaps, vector<bool>& down, vector<int>& arr, int n) {
  for (int i = 0; i < n; ++i)
    while (down[i] && !down[arr[i]]) swaps.push_back({i, arr[i]}), swap(arr[i], arr[arr[i]]);
  for (int i = 0; i < n; ++i)
    if (down[i]) swaps.push_back({i, arr[i]}), down[i] = down[arr[i]] = false, swap(arr[i], arr[arr[i]]);
}

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) --arr[i];
  vector<pii> swaps;
  vector<bool> down(n), vis(n);
  int last = -1, ls = 0;
  for (int i = 0; i < n; ++i) {
    if (vis[i]) continue;
    int sz = 0;
    while (!vis[i]) vis[i] = true, i = arr[i], ++sz;
    if (last < 0) {
      last = i, ls = sz;
      continue;
    }
    swaps.push_back({i, last}), down[i] = down[last] = true, swap(arr[i], arr[last]), last = -1;
  }
  fix(swaps, down, arr, n);
  if (last >= 0 && ls > 1) {
    if (last) swaps.push_back({0, last}), down[0] = down[last] = true, swap(arr[0], arr[last]);
    else {
      int a = 0, b = arr[0], c = arr[arr[0]];
      swaps.push_back({a, b}), down[a] = down[b] = true, swap(arr[a], arr[b]);
      swaps.push_back({b, c}), swap(arr[b], arr[c]);
    }
  }
  fix(swaps, down, arr, n);
  cout << swaps.size() << '\n';
  for (pii p : swaps) cout << p.first + 1 << ' ' << p.second + 1 << '\n';
  return 0;
}

