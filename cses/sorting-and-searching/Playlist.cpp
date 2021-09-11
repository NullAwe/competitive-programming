#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Finds answer using two pointers:
  set<int> has;
  int l = 0, r = 0, ans = 1;
  has.insert(arr[0]);
  while (r < arr.size() - 1) {
    ++r;
    while (has.count(arr[r])) has.erase(arr[l++]);
    has.insert(arr[r]);
    ans = max(ans, r - l + 1);
  }
  // Output:
  cout << ans << endl;
  return 0;
}
