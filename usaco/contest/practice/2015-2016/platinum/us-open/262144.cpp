#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("262144.in");
  ofstream out("262144.out");
  int n; in >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) in >> arr[i];
  vector<vector<int>> to(n, vector<int>(60, -1));
  for (int i = 0; i < n; ++i) to[i][arr[i]] = i + 1;
  for (int i = 2; i < to[0].size(); ++i) {
    for (int j = 0; j < n; ++j) {
      if (to[j][i - 1] == -1 || to[j][i - 1] == n) continue;
      to[j][i] = to[to[j][i - 1]][i - 1];
    }
  }
  for (int i = to[0].size() - 1; i >= 0; --i) {
    for (int j = 0; j < n; ++j) {
      if (to[j][i] >= 0) {
        out << i << '\n';
        return 0;
      }
    }
  }
  return 0;
}
