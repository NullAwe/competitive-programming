#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, q; cin >> n >> q;
  string str; cin >> str;
  vector<ll> disjoint(n + 1), prefix(n + 1);
  stack<int> indices;
  for (int i = 0; i < n; ++i) {
    if (str[i] == '(') indices.push(i);
    else if (indices.size()) {
      int top = indices.top(); indices.pop();
      disjoint[i + 1] = disjoint[top] + 1;
    }
    prefix[i + 1] = prefix[i] + disjoint[i + 1];
  }
  for (int i = 0; i < q; ++i) {
    int t, l, r; cin >> t >> l >> r;
    cout << prefix[r] - prefix[l - 1] - disjoint[l - 1] * (disjoint[r] - disjoint[l - 1]) << endl;
  }
  return 0;
}
