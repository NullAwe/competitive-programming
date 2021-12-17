#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

#define pin pair<int, node>

struct node {
  int pos, dir, brd;
  node(int p, int d, int b) { pos = p, dir = d, brd = b; }
};

int main() {
  int n, k; cin >> n >> k;
  vector<int> breeds(n); for (int i = 0; i < n; ++i) cin >> breeds[i];
  for (int i = 0; i < n; ++i) --breeds[i];
  vector<vector<bool>> adj(k, vector<bool>(k, false));
  for (int i = 0; i < k; ++i) {
    string str; cin >> str;
    for (int j = 0; j < k; ++j) if (str[j] == '1') adj[i][j] = true;
  }
  // Finds answer using 0-1 BFS:
  vector<vector<vector<int>>> dists(n, vector<vector<int>>(2, vector<int>(k, -1)));
  queue<pin> q;
  q.push({0, node(0, 1, breeds[0])});
  while (q.size()) {
    pin now = q.front(); q.pop();
    node nod = now.second;
    vector<node> next;
    if (adj[nod.brd][breeds[nod.pos]]) {
      if (nod.pos > 0) next.push_back(node(nod.pos - 1, 0, breeds[nod.pos]));
	  if (nod.pos < n - 1) next.push_back(node(nod.pos + 1, 1, breeds[nod.pos]));
    }
    if (!(nod.pos == 0 && nod.dir == 0) && !(nod.pos == n - 1 && nod.dir == 1)) {
      int nextPos = nod.pos + (nod.dir == 1 ? 1 : -1);
      next.push_back(node(nextPos, nod.dir, nod.brd));
    }
    for (node nxt : next) if (dists[nxt.pos][nxt.dir][nxt.brd] < 0) {
      q.push({now.first + 1, nxt});
      dists[nxt.pos][nxt.dir][nxt.brd] = now.first + 1;
    }
  }
  int m = INF;
  for (int i = 0; i < k; ++i) if (adj[i][breeds[n - 1]] && dists[n - 1][1][i] < INF) m = min(m, dists[n - 1][1][i]);
  // Output:
  cout << (m == INF ? -1 : m) << endl;
  return 0;
}
