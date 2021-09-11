#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n, mm; cin >> n >> mm;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> m(n + 1);
  for (int i = 0; i < n; ++i) m[arr[i]] = i;
  int ans = 1;
  for (int i = 2; i <= n; ++i) if (m[i - 1] > m[i]) ++ans;
  for (int i = 0; i < mm; ++i) {
    int xi, yi; cin >> xi >> yi;
    int x = arr[xi - 1], y = arr[yi - 1];
    // Removes the old values:
    if (x > 1 && m[x - 1] > m[x]) --ans;
    if (x < n && m[x] > m[x + 1]) --ans;
    if (y > 1 && x != y - 1 && m[y - 1] > m[y]) --ans;
    if (y < n && x != y + 1 && m[y] > m[y + 1]) --ans;
    // Adds the new values:
    int tmp = m[x];
    m[x] = m[y];
    m[y] = tmp;
    tmp = arr[xi - 1];
    arr[xi - 1] = arr[yi - 1];
    arr[yi - 1] = tmp;
    if (x > 1 && m[x - 1] > m[x]) ++ans;
    if (x < n && m[x] > m[x + 1]) ++ans;
    if (y > 1 && x != y - 1 && m[y - 1] > m[y]) ++ans;
    if (y < n && x != y + 1 && m[y] > m[y + 1]) ++ans;
    // Output:
    cout << ans << endl;
  }
  return 0;
}
