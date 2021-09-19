#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, m; cin >> n >> m;
  // Outputs for a special case:
  if (n == 1 && m == 1) {
    cout << "YES\n1" << endl;
    return 0;
  }
  // Outputs for a special case:
  if (n == 3 && m == 3) {
    cout << "YES\n1 6 8\n7 2 4\n5 9 3" << endl;
    return 0;
  }
  // Outputs for a special case:
  if (max(n, m) < 4) {
    cout << "NO" << endl;
    return 0;
  }
  // Initial output:
  cout << "YES" << endl;
  // Finds row/column mix-ups:
  int sz = m;
  if (sz < 4) sz = n;
  vector<int> p1(sz), p2(sz);
  for (int i = 0; i < sz / 2; ++i) p1[i] = i * 2 + 2;
  for (int i = sz / 2; i < sz; ++i) p1[i] = (i - sz / 2) * 2 + 1;
  if (sz % 2 == 0) {
    for (int i = 0; i < sz / 2; ++i) p2[i] = sz - i * 2 - 1;
    for (int i = sz / 2; i < sz; ++i) p2[i] = sz - (i - sz / 2) * 2;
  } else {
    for (int i = 0; i <= sz / 2; ++i) p2[i] = i * 2 + 1;
    for (int i = sz / 2 + 1; i < sz; ++i) p2[i] = (i - sz / 2 - 1) * 2 + 2;
  }
  // Output:
  if (sz == m) {
    for (int i = 0; i < n; ++i) {
      if (i % 2 == 0) for (int num : p1) cout << num + i * m << ' ';
      else for (int num : p2) cout << num + i * m << ' ';
      cout << endl;
    }
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (j % 2 == 0) cout << (p1[i] - 1) * m + j + 1 << ' ';
      else cout << (p2[i] - 1) * m + j + 1 << ' ';
    }
    cout << endl;
  }
  return 0;
}
