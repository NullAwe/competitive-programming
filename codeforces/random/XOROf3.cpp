#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Checks if the array works:
  int ones = 0;
  for (int num : arr) ones += num;
  if (ones % 2 == 1 || ones == n) {
    // Output:
    cout << "NO" << endl;
    return;
  }
  vector<int> moves;
  int row = 0;
  // Scans forwards throughout the array once to prepare it:
  for (int i = 0; i < n; ++i) {
    if (arr[i] == 0) row = 0;
    else ++row;
    if (i < n - 2 && arr[i + 1] == 0 && row % 2 == 1) {
      moves.push_back(i + 1);
      int replace = arr[i] ^ arr[i + 1] ^ arr[i + 2];
      arr[i] = arr[i + 1] = arr[i + 2] = replace;
    }
  }
  // Checks if array works one more time:
  ones = 0;
  for (int num : arr) ones += num;
  if (ones % 2 == 1 || ones == n) {
    // Output:
    cout << "NO" << endl;
    return;
  }
  // Scans the array backwards to finish the problem:
  row = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (arr[i] == 0) break;
    ++row;
  }
  for (int i = row; i > 1; i -= 2) moves.push_back(n - i);
  for (int i = n - row; i < n; ++i) arr[i] = 0;
  for (int i = n - 3; i >= 0; --i) {
    if (arr[i] == 1 && arr[i + 1] == 1 && arr[i + 2] == 0) {
      moves.push_back(i + 1);
      arr[i] = arr[i + 1] = 0;
    }
  }
  // Output:
  cout << "YES\n" << moves.size() << endl;
  for (int num : moves) cout << num << ' ';
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
