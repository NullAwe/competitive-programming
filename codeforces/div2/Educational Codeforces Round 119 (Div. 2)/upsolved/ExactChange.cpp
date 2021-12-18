#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  set<int> s; for (int num : arr) s.insert(num);
  // D: Finds answer using casework:
  if (n == 1) cout << arr[0] / 3 + (arr[0] % 3 == 0 ? 0 : 1) << endl;
  else {
    if (arr[0] == 1) {
      if (arr[1] == 2) {
        if (arr[n - 1] % 3 == 0) cout << arr[n - 1] / 3 + 1 << endl;
        else cout << arr[n - 1] / 3 + 2 << endl;
      } else {
        bool two = false;
        for (int num : arr) if (num % 3 == 2) { two = true; break; }
        if (two && arr[n - 1] % 3 == 0) cout << arr[n - 1] / 3 + 1 << endl;
        else if (two) cout << arr[n - 1] / 3 + 2 << endl;
        else cout << arr[n - 1] / 3 + 1 << endl;
      }
    } else {
      set<int> mods;
      for (int num : arr) if (num % 3) mods.insert(num % 3);
      if (mods.size() == 0) cout << arr[n - 1] / 3 << endl;
      else if (mods.size() == 1) cout << arr[n - 1] / 3 + 1 << endl;
      else if ((!s.count(arr[n - 1] / 3 * 3) && arr[n - 1] % 3 == 1) || arr[n - 1] % 3 == 0)
        cout << arr[n - 1] / 3 + 1 << endl;
      else cout << arr[n - 1] / 3 + 2 << endl;
    }
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}