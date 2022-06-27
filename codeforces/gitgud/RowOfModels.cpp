#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  map<int, int> m; for (int i = 0; i < n; ++i) if (!m[arr[i]]) m[arr[i]] = i + 1;
  sort(arr.begin(), arr.end());
  int l = 0, s = n - k, us = n - k;
  for (int i = 0; i < n; ++i) {
    if (arr[i] == l) continue;
    l = arr[i];
    int pos = m[arr[i]] - 1;
    if (us >= 0 && pos >= us) s = min(min(s, max(pos - k, 0)), max(us - k, 0)), us = min(us, max(pos - k, 0));
    else if (pos >= s) s = min(s, max(pos - k, 0));
    else {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
}

