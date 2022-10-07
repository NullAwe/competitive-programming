#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void solve() {
  int n; cin >> n;
  int arr[n]; for (int i = 0; i < n; ++i) cin >> arr[i];
  int mn = arr[0], ind = 0;
  for (int i = 1; i < n; ++i) if ((mn & 1) == (arr[i] & 1) && arr[i] < mn) mn = arr[i], ind = i;
  vector<pii> swaps;
  if (ind) swaps.push_back({0, ind}), arr[0] = arr[ind];
  for (int i = 1; i < n; ++i) if ((arr[0] & 1) != (arr[i] & 1)) swaps.push_back({0, i}), arr[i] = arr[0];
  ind = 0;
  for (int i = 0; i < n; ++i) if (arr[i] == arr[0]) ind = i;
  for (int i = 0; i < ind; ++i) if (arr[i] != arr[0]) swaps.push_back({i, ind}), arr[i] = arr[ind];
  for (int i = ind + 1; i < n - 1; ++i) swaps.push_back({i, n - 1}), arr[i] = arr[n - 1];
  cout << swaps.size() << '\n';
  for (pii swap : swaps) cout << swap.first + 1 << ' ' << swap.second + 1 << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
