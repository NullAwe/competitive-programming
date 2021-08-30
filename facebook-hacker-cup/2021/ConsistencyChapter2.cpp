#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    string str; cin >> str;
    int n; cin >> n;
    vector<vector<int>> adj(26, vector<int>(26)), distance(26, vector<int>(26));
    for (int j = 0; j < n; ++j) {
      string edge; cin >> edge;
      int a = edge[0] - 'A', b = edge[1] - 'A';
      adj[a][b] = 1;
    }
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
        if (i == j) distance[i][j] = 0;
        else if (adj[i][j]) distance[i][j] = adj[i][j];
        else distance[i][j] = INF;
      }
    }
    // Finds minimum distance for every pair using Floyd-Warshall:
    for (int k = 0; k < 26; ++k)
      for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j)
          distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
    int m = INT_MAX;
    // Checks number of operations to make string consistent with all possible consistent strings:
    for (int j = 0; j < 26; ++j) {
      int secs = 0;
      for (int k = 0; k < str.size(); ++k) {
        int id = str[k] - 'A';
        if (distance[id][j] == INF) {
          secs = INT_MAX;
          break;
        }
        secs += distance[id][j];
      }
      m = min(m, secs);
    }
    if (m == INT_MAX) m = -1;
    // Output:
    cout << "Case #" << i << ": " << m << endl;
  }
  return 0;
}
