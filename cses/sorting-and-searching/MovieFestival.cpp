#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n; cin >> n;
  vector<vector<int>> movies(n, vector<int>(2));
  for (int i = 0; i < n; ++i) cin >> movies[i][1] >> movies[i][0];
  sort(movies.begin(), movies.end());
  int end = 0, ans = 0;
  for (int i = 0; i < movies.size(); ++i) {
    if (movies[i][1] >= end) {
      end = movies[i][0];
      ++ans;
    }
  }
  cout << ans << endl;
  return 0;
}
