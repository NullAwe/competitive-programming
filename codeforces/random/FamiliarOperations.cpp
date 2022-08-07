#include <bits/stdc++.h>
using namespace std;

const int MAX_X = 1e6 + 1;
const int MAX_IDG = 300;
const int INF = 1e9;

vector<int> id(MAX_X);
vector<vector<int>> vals(MAX_IDG);
vector<vector<int>> group(MAX_IDG);
vector<vector<vector<int>>> to(MAX_IDG, vector<vector<int>>(9, vector<int>(MAX_IDG, INF)));

void solve() {
  int a, b, ans = INF; cin >> a >> b; a = id[a], b = id[b];
  for (int g = 1; g < MAX_IDG; ++g) ans = min(ans, to[a][8][g] + to[b][8][g]);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  map<vector<int>, int> inc;
  vector<int> prods(MAX_IDG);
  int cur = 1;
  for (int i = 1; i < MAX_X; ++i) {
    int prod = 1, n = i;
    vector<int> facts;
    for (int j = 2; j * j <= n; ++j) {
      int count = 0;
      while (n % j == 0) n /= j, ++count;
      if (count) facts.push_back(count), prod *= count + 1;
    }
    if (n > 1) facts.push_back(1), prod *= 2;
    while (facts.size() < 8) facts.push_back(0);
    sort(facts.begin(), facts.end());
    if (!inc[facts]) inc[facts] = cur, prods[cur] = prod, vals[cur++] = facts;
    id[i] = inc[facts];
  }
  for (int i = 0; i < MAX_IDG; ++i) to[i][0][1] = 0;
  for (int i = 1; i < cur; ++i) {
    int g = 1;
    for (int num : vals[i]) g *= num + 1;
    group[g].push_back(i);
    for (int j = 1; j < 9; ++j) {
      for (int k = 1; k < MAX_IDG; ++k) {
        for (int l = 1; l * l <= k; ++l) {
          if (k % l) continue;
          vector<int> perf; perf.push_back(l);
          if (l * l < k) perf.push_back(k / l);
          for (int num : perf) to[i][j][k] = min(to[i][j][k], to[i][j - 1][k / num] + abs(vals[i][j - 1] + 1 - num));
        }
      }
    }
  }
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

