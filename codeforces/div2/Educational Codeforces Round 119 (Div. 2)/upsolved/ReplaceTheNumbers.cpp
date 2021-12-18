#include <bits/stdc++.h>
using namespace std;

void solve() {
  int q; cin >> q;
  vector<vector<int>*> m(500001);
  set<int> avail;
  int ind = 0;
  for (int i = 0; i < q; ++i) {
    int type; cin >> type;
    vector<int>* v = new vector<int>();
    if (type == 1) {
      int val; cin >> val;
      if (!avail.count(val)) {
        v->push_back(ind++);
        m[val] = v;
      } else m[val]->push_back(ind++);
      avail.insert(val);
    } else {
      // Small to large merging:
      int a, b; cin >> a >> b;
      if (!avail.count(a) || a == b) continue;
      if (avail.count(b)) {
        if (m[b]->size() < m[a]->size()) swap(m[a], m[b]);
        for (int num : (*m[a])) m[b]->push_back(num);
      } else m[b] = m[a];
      m[a] = v;
      avail.erase(a); avail.insert(b);
    }
  }
  vector<int> arr(ind);
  for (int num : avail) for (int i : *m[num]) arr[i] = num;
  // Output:
  for (int num : arr) cout << num << ' ';
  cout << endl;
}

int main() {
  solve();
  return 0;
}