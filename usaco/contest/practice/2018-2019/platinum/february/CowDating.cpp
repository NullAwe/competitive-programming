#include <bits/stdc++.h>
using namespace std;

const double MULT = 1000000;

int main() {
  ifstream in("cowdate.in");
  ofstream out("cowdate.out");
  int n; in >> n;
  vector<double> arr(n), p(n + 1); for (int i = 0; i < n; ++i) { int x; in >> x; arr[i] = x / MULT; }
  for (int i = 0; i < n; ++i) p[i + 1] = p[i] + arr[i] / (1 - arr[i]);
  int r = 0, ll = 0, lr = 0;
  double prod = 1 - arr[0], ans = 0;
  for (int i = 0; i < n; ++i) {
    if (r < i) ++r;
    while (r < n && p[r + 1] - p[i] < 1) ++r;
    while (ll < min(i, lr)) prod /= 1 - arr[ll++];
    while (ll < i) prod /= 1 - arr[ll++], prod *= 1 - arr[++lr];
    while (lr < r) prod *= 1 - arr[++lr];
    ans = max(ans, (p[r + 1] - p[i]) * prod);
  }
  out << (int) (ans * MULT) << '\n';
  return 0;
}
