#include <bits/stdc++.h>
using namespace std;

vector<int> zf(vector<int>& arr) {
  int n = arr.size();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && arr[z[i]] == arr[i + z[i]]) ++z[i];
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}

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
    }
    vector<int> combine(3 * n + 1);
    for (int j = 0; j < n; ++j) combine[j] = b[j];
    b[n] = -1;
    for (int j = 0; j < n; ++j) combine[j + n + 1] = combine[j + 2 * n + 1] = a[j];
    vector<int> z = zf(combine);
    int correct = 0;
    for (int i = n + 1; i <= 2 * n; ++i) correct += z[i] == n;
    if (!correct) {
      out << "Case #" << i << ": " << "NO\n";
      continue;
    } else if (correct == 1 && k == 1 && a == b) {
      out << "Case #" << i << ": " << "NO\n";
      continue;
    } else if (correct == 1 && n == 2 && ((a == b && k % 2) || (a[0] == b[1] && a[1] == b[0] && k % 2 == 0))) {
      out << "Case #" << i << ": " << "NO\n";
      continue;
    }
    out << "Case #" << i << ": " << "YES\n";
  }
  return 0;
}
