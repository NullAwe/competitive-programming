#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, x; cin >> n >> x;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  // Finds answer using greedy and two pointers:
  int left = 0, right = n - 1, ans = 0;
  while (left <= right) {
    if (left == right || arr[left] + arr[right] > x) --right, ++ans;
    else ++left, --right, ++ans;
  }
  // Output:
  cout << ans << endl;
  return 0;
}
