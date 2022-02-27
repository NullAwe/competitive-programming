#include <iostream>
#include <vector>
using namespace std;

#define ll long long

const int MAX_VAL = 2e6 + 1;
const int MAX_C = 1e6;

void update(vector<int>& t, int n, int p, int v) {
  for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(vector<int>& t, int n, int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

int main() {
  int n; cin >> n;
  vector<vector<int>> add(MAX_VAL), remove(MAX_VAL);
  vector<vector<pair<int, int>>> queries(MAX_VAL);
  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2) {
      add[min(y1, y2) + MAX_C].push_back(x1 + MAX_C);
      remove[max(y1, y2) + MAX_C].push_back(x1 + MAX_C);
    } else {
      queries[y1 + MAX_C].push_back({min(x1, x2) + MAX_C, max(x1, x2) + MAX_C});
    }
  }
  vector<int> t(2 * MAX_VAL);
  ll ans = 0;
  for (int i = 0; i < MAX_VAL; ++i) {
    for (int num : add[i]) update(t, MAX_VAL, num, t[num + MAX_VAL] + 1);
    for (int num : remove[i]) update(t, MAX_VAL, num, t[num + MAX_VAL] - 1);
    for (pair<int, int> q : queries[i]) ans += query(t, MAX_VAL, q.first, q.second);
  }
  cout << ans << endl;
}
