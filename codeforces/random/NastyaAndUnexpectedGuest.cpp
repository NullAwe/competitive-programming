#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define getID(i, j, g) ((i) * (g) + (j))
#define getNode(id, g) ((id) / (g))
#define getTime(id, g) ((id) % (g))

int main() {
  int n, m; cin >> n >> m;
  vector<int> safe(m); for (int i = 0; i < m; ++i) cin >> safe[i];
  sort(safe.begin(), safe.end());
  int g, r; cin >> g >> r;
  vector<ll> dists(m * (g + 1), -1); dists[getID(0, g, g + 1)] = 0;
  deque<int> dq; dq.push_back(getID(0, g, g + 1));
  while (dq.size()) {
    int id = dq.front(); dq.pop_front();
    int place = getNode(id, g + 1), time = getTime(id, g + 1);
    if (place > 0 && safe[place] - safe[place - 1] <= time) {
      ll weight = abs(safe[place] - safe[place - 1]);
      int nextTime = time - weight;
      if (weight == time) {
        weight += r;
        nextTime = g;
      }
      int next = getID(place - 1, nextTime, g + 1);
      if (dists[next] < 0) {
        dists[next] = dists[id] + weight;
        if (nextTime == g) dq.push_back(next);
        else dq.push_front(next);
      }
    }
    if (place < m - 1 && safe[place + 1] - safe[place] <= time) {
      ll weight = abs(safe[place + 1] - safe[place]);
      int nextTime = time - weight;
      if (weight == time) {
        weight += r;
        nextTime = g;
      }
      int next = getID(place + 1, nextTime, g + 1);
      if (dists[next] < 0) {
        dists[next] = dists[id] + weight;
        if (nextTime == g) dq.push_back(next);
        else dq.push_front(next);
      }
    }
  }
  dists[getID(m - 1, g, g + 1)] -= r;
  ll ans = LLONG_MAX;
  for (int i = 0; i <= g; ++i) {
    ll val = dists[getID(m - 1, i, g + 1)];
    if (val >= 0) ans = min(ans, val);
  }
  // Output:
  cout << (ans == LLONG_MAX ? -1 : ans) << endl;
  return 0;
}
