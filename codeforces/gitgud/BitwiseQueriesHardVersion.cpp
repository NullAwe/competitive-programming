#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> xors(n - 1);
  for (int i = 2; i <= n; ++i) {
    printf("XOR %d %d\n", 1, i);
    fflush(stdout);
    scanf("%d", &xors[i - 2]);
  }
  // Finds the first number with at most two queries:
  map<int, int> m;
  set<int> included;
  int i1 = -1, i2 = -1;
  for (int i = 0; i < n - 1; ++i) {
    if (included.count(xors[i])) {
      i1 = m[xors[i]];
      i2 = i;
      break;
    }
    m[xors[i]] = i;
    included.insert(xors[i]);
  }
  vector<int> ans(n);
  if (i1 >= 0 && i2 >= 0) {
    printf("AND %d %d\n", i1 + 2, i2 + 2);
    fflush(stdout);
    int t; scanf("%d", &t);
    ans[0] = t ^ xors[i1];
  } else if (included.count(0)) {
    printf("AND %d %d\n", 1, m[0] + 2);
    fflush(stdout);
    scanf("%d", &ans[0]);
  } else {
    printf("AND %d %d\n", 1, m[1] + 2);
    fflush(stdout);
    int res1; scanf("%d", &res1);
    printf("AND %d %d\n", 1, m[n - n / 2] + 2);
    fflush(stdout);
    int res2; scanf("%d", &res2);
    ans[0] = (res1 & (n - 2)) | (res2 & (n - 1 - (n - n / 2)));
  }
  for (int i = 0; i < n - 1; ++i) ans[i + 1] = ans[0] ^ xors[i];
  // Output:
  cout << '!';
  for (int num : ans) cout << ' ' << num;
  cout << endl;
  return 0;
}
