#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 1;

vector<int> init[MAX_N], adj[MAX_N];
int sizes[MAX_N], dists[MAX_N];

int fill(int node, int parent, int dist) {
  ++sizes[node]; dists[node] = dist;
  for (int next : init[node]) {
    if (next != parent) {
      adj[node].push_back(next);
      sizes[node] += fill(next, node, dist + 1);
    }
  }
  return sizes[node];
}

int main() {
  int n; cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    init[a].push_back(b);
    init[b].push_back(a);
  }
  fill(0, -1, 0);
  printf("d %d\n", 1); fflush(stdout);
  int dx; scanf("%d", &dx);
  int ans = -1, curNode = 0; if (dx == 0) ans = 0;
  while (ans < 0) {
    printf("s %d\n", curNode + 1); fflush(stdout);
    int sec; scanf("%d", &sec); --sec;
    int bottom = sec;
    while (sizes[bottom] > 1) {
      int next = -1, maxSize = 0;
      for (int num : adj[bottom]) {
        if (sizes[num] > maxSize) {
          next = num;
          maxSize = sizes[num];
        }
      }
      bottom = next;
    }
    printf("d %d\n", bottom + 1); fflush(stdout);
    int dist; scanf("%d", &dist);
    int diff = (dists[bottom] + dx - dist) >> 1;
    bottom = sec;
    for (int i = 1; i < diff - dists[curNode]; ++i) {
      int next = -1, maxSize = 0;
      for (int num : adj[bottom]) {
        if (sizes[num] > maxSize) {
          next = num;
          maxSize = sizes[num];
        }
      }
      bottom = next;
    }
    if (diff == dx) ans = bottom;
    curNode = bottom;
  }
  // Output:
  cout << "! " << ans + 1 << endl;
  return 0;
}
