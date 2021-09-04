#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MOD = 1000000007;

int main() {
  int n; cin >> n;
  string str; cin >> str;
  string match = "abc";
  // Calculates answer using dynamic programming:
  vector<vector<ll>> memo(n + 1, vector<ll>(match.size() + 1));
  memo[n][match.size()] = 1;
  for (int i = n - 1; i >= 0; --i) {
    memo[i][match.size()] = memo[i + 1][match.size()];
    if (str[i] == '?') memo[i][match.size()] *= 3;
    memo[i][match.size()] %= MOD;
  }
  for (int i = match.size() - 1; i >= 0; --i) {
    for (int j = n - 1; j >= 0; --j) {
      memo[j][i] = memo[j + 1][i];
      if (str[j] == '?') memo[j][i] *= 3;
      if (str[j] == match[i] || str[j] == '?') memo[j][i] += memo[j + 1][i + 1];
      memo[j][i] %= MOD;
    }
  }
  // Output:
  cout << memo[0][0] << endl;
  return 0;
}
