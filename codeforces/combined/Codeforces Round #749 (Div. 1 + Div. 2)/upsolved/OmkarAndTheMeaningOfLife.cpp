#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> bigger(n, -1), smaller(n, -1);
  for (int i = 0; i < n; ++i) {
    vector<int> b(n, 2), s(n, 1);
    b[i] = 1; s[i] = 2;
    string q = "?";
    for (int num : b) q += " " + to_string(num);
    printf("%s\n", q.c_str());
    fflush(stdout);
    int res; scanf("%d", &res);
    if (res != i + 1) {
      smaller[i] = res - 1;
      bigger[res - 1] = i;
    }
    q = "?";
    for (int num : s) q += " " + to_string(num);
    printf("%s\n", q.c_str());
    fflush(stdout);
    scanf("%d", &res);
    if (res != i + 1) {
      bigger[i] = res - 1;
      smaller[res - 1] = i;
    }
  }
  // Constructs the answer:
  vector<int> ans(n);
  int cur = -1;
  for (int i = 0; i < n; ++i) if (smaller[i] < 0) cur = i;
  for (int i = 1; i <= n; ++i) {
    ans[cur] = i;
    cur = bigger[cur];
  }
  // Output:
  cout << '!';
  for (int num : ans) cout << ' ' << num;
  cout << endl;
  return 0;
}
