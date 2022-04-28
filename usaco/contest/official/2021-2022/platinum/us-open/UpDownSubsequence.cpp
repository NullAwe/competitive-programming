#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  string str; cin >> str;
  set<int> seq; seq.insert(arr[0]);
  int cur = 0;
  for (int i = 1; i < n; ++i) {
    if ((str[cur] == 'D' && *seq.begin() > arr[i]) || (str[cur] == 'U' && *--seq.end() < arr[i])) {
      seq.insert(arr[i]);
      ++cur;
      if (cur == n - 1) break;
      if (str[cur] != str[cur - 1]) {
        seq.clear();
        seq.insert(arr[i]);
      }
    } else {
      auto it = seq.upper_bound(arr[i]);
      if (str[cur] == 'D') --it;
      seq.erase(it); seq.insert(arr[i]);
    }
  }
  cout << cur << '\n';
}
