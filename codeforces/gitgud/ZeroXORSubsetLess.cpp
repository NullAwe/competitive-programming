#include <bits/stdc++.h>
using namespace std;

int n, m = 30, _rank = 0;

void add(int x, vector<int>& tracker) {
  for (int i = 0; i < m; ++i) {
    if (!((x >> i) & 1)) continue;
    if (!tracker[i]) {
      tracker[i] = x;
      ++_rank;
      return;
    }
    x ^= tracker[i];
  }
}

int main() {
  cin >> n;
  vector<int> tracker(m);
  int x = 0;
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    x ^= a;
    add(x, tracker);
  }
  // Output:
  if (x == 0) cout << -1 << endl;
  else cout << _rank << endl;
  return 0;
}
