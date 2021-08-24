#include <bits/stdc++.h>
using namespace std;

// Reverses the first (num) values in an array:
void rev(vector<int>& arr, int num) {
  for (int i = 0; i < num / 2; ++i) {
    int tmp = arr[i];
    arr[i] = arr[num - i - 1];
    arr[num - i - 1] = tmp;
  }
}

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> revs;
  for (int i = 1; i < n - 1; i += 2) {
    // Adds reversals such that [i + 1, i] will be put at the end of the array
    // (to the left of [i - 1, i - 2, ...]):
    int ind1 = -1, ind2 = -1;
    for (int j = 0; j < n; ++j) {
      if (arr[j] == i) ind1 = j;
      else if (arr[j] == i + 1) ind2 = j;
    }
    if (ind1 % 2 == 1 || ind2 % 2 == 0) {
      // It is impossible to sort the array:
      cout << -1 << endl;
      return;
    }
    if (ind1 == n - i && ind2 == ind1 - 1) continue;
    if (ind1 != 0) {
      revs.push_back(ind1 + 1);
      rev(arr, ind1 + 1);
      if (ind2 < ind1) ind2 = ind1 - ind2;
    }
    if (ind2 != 1) {
      revs.push_back(ind2);
      rev(arr, ind2);
      revs.push_back(ind2 + 2);
      rev(arr, ind2 + 2);
      revs.push_back(3);
      rev(arr, 3);
    }
    revs.push_back(n - i + 1);
    rev(arr, n - i + 1);
  }
  // Array is sorted in descending order, so we have to reverse the entire array.
  revs.push_back(n);
  // Output:
  cout << revs.size() << endl;
  for (int num : revs) cout << num << " ";
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
