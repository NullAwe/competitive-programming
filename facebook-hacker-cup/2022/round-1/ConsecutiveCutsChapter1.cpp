#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("in.txt");
  ofstream out("out.txt");
  int t; in >> t;
  for (int i = 1; i <= t; ++i) {
    int n, k; in >> n >> k;
    vector<int> a(n), b(n);
    for (int j = 0; j < n; ++j) in >> a[j];
    for (int j = 0; j < n; ++j) in >> b[j];
    if (!k) {
      out << "Case #" << i << ": " << (a == b ? "YES" : "NO") << '\n';
      continue;
    } else if (k == 1 && a == b) {
      out << "Case #" << i << ": " << "NO\n";
      continue;
    } else if (n == 2 && ((a == b && k % 2) || (a[0] == b[1] && a[1] == b[0] && k % 2 == 0))) {
      out << "Case #" << i << ": " << "NO\n";
      continue;
    }
    int j;
    for (j = 0; j < n && a[0] != b[j]; ++j);
    vector<int> c(n); for (int l = 0; l < n; ++l) c[l] = b[(j + l) % n];
    out << "Case #" << i << ": " << (a == c ? "YES" : "NO") << '\n';
  }
  return 0;
}
