#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& arr, int l, int r) {
  if (l >= r) return 0;
  // Finds the first 0 in the array:
  int ind = -1;
  for (int i = l; i < r; ++i) {
    if (arr[i] == 0) {
      ind = i;
      break;
    }
  }
  if (ind < 0) {
    int m = INT_MAX;
    for (int i = l; i < r; ++i) m = min(m, arr[i]);
    for (int i = l; i < r; ++i) arr[i] -= m;
    // Finds the answer, which is the minimum of using the first operation and not:
    return min(m + solve(arr, l, r), r - l);
  }
  // Finds the answer in this case, which is the answer of the array left of the 0
  // added to the answer of the array right of the 0:
  return solve(arr, l, ind) + solve(arr, ind + 1, r);
}

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Output:
  cout << solve(arr, 0, n) << endl;
  return 0;
}
