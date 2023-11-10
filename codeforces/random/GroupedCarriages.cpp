#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

bool check(int n, vector<int> a, vector<int>& b, int cap) {
  vector<pii> cars(n);
  for (int i = 0; i < n; ++i) cars[i] = {i + b[i], i};
  sort(cars.begin(), cars.end());
  vector<int> caps(n, cap);
  set<int> l; for (int i = 0; i < n; ++i) l.insert(i);
  for (pii car : cars) {
    while (a[car.second]) {
      auto it = l.lower_bound(car.second - b[car.second]);
      if (it == l.end() || *it > car.first) {
        return false;
      }
      int rem = min(a[car.second], caps[*it]);
      caps[*it] -= rem;
      a[car.second] -= rem;
      if (caps[*it] == 0) l.erase(it);
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> arr(n);
  vector<int> b(n);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  int lo = -1, hi = 1000000001;
  while (lo < hi - 1) {
    int md = (lo + hi) / 2;
    if (check(n, arr, b, md)) hi = md;
    else lo = md;
  }
  cout << hi << '\n';
  return 0;
}