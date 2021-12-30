#include <bits/stdc++.h>
using namespace std;

const int MAX_X = 8192;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<int>> can(MAX_X); for (int i = 0; i < MAX_X; ++i) can[i].push_back(0);
  vector<int> top(MAX_X); for (int i = 0; i < MAX_X; ++i) top[i] = MAX_X - 1;
  vector<bool> ans(MAX_X, false); ans[0] = true;
  for (int i = 0; i < n; ++i) {
    for (int num : can[arr[i]]) {
      int x = arr[i] ^ num;
      ans[x] = true;
      while (top[x] > arr[i]) can[top[x]--].push_back(x);
    }
    can[arr[i]].resize(0);
  }
  int count = 0; for (bool b : ans) if (b) ++count;
  // Output:
  cout << count << endl;
  for (int i = 0; i < MAX_X; ++i) if (ans[i]) cout << i << ' ';
  cout << endl;
  return 0;
}
