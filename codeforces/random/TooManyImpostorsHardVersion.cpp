#include <bits/stdc++.h>
using namespace std;

int query(int a, int b, int c) {
  printf("? %d %d %d\n", a, b, c); fflush(stdout);
  int res; scanf("%d", &res);
  if (res < 0) exit(0);
  return res;
}

void solve() {
  int n; cin >> n;
  vector<int> threes(n / 3);
  for (int i = 0; i < n / 3; ++i) threes[i] = query(i * 3 + 1, i * 3 + 2, i * 3 + 3);
  int impostor = -1, crewmate = -1;
  for (int i = 1; i < n / 3; ++i) {
    if (threes[i - 1] != threes[i]) {
      int a = query(i * 3 - 1, i * 3, i * 3 + 1), b = query(i * 3, i * 3 + 1, i * 3 + 2);
      vector<int> vals = {threes[i - 1], a, b, threes[i]};
      int fm = 0;
      if (a != b) fm = 1;
      else if (b != threes[i]) fm = 2;
      impostor = i * 3 - 2 + fm, crewmate = i * 3 + 1 + fm;
      if (vals[fm]) swap(impostor, crewmate);
      break;
    }
  }
  set<int> impostors; impostors.insert(impostor);
  for (int i = 0; i < n / 3; ++i) {
    int a = i * 3 + 1, b = i * 3 + 2, c = i * 3 + 3;
    if (abs(b - impostor) < 2 || abs(b - crewmate) < 2) {
      int first = a, second = b;
      if (a == impostor || a == crewmate) first = c;
      else if (b == impostor || b == crewmate) second = c;
      if (!query(first, impostor, crewmate)) impostors.insert(first);
      if (!query(second, impostor, crewmate)) impostors.insert(second);
    } else {
      if (!threes[i]) {
        if (!query(crewmate, a, b)) {
          impostors.insert(a); impostors.insert(b);
          if (!query(c, impostor, crewmate)) impostors.insert(c);
        } else {
          impostors.insert(c);
          impostors.insert(query(a, impostor, crewmate) ? b : a);
        }
      } else {
        if (query(impostor, a, b)) {
          if (!query(c, impostor, crewmate)) impostors.insert(c);
        } else impostors.insert(query(a, impostor, crewmate) ? b : a);
      }
    }
  }
  // Output:
  cout << "! " << impostors.size();
  for (int num : impostors) cout << ' ' << num;
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
