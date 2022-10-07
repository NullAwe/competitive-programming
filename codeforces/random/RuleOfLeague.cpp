#include <iostream>
using namespace std;

void solve() {
  int n, x, y; cin >> n >> x >> y;
  int nx = min(x, y), ny = max(x, y);
  if (nx || !ny || (n - 1) % ny) {
    cout << -1 << '\n';
    return;
  }
  for (int i = 0; i < (n - 1) / ny; ++i) for (int j = 0; j < ny; ++j) cout << i * ny + 1 + (i > 0) << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
