#include <bits/stdc++.h>
using namespace std;

int dim, q, a1, b1, a2, b2, trees[1000][1000];
string line;

int getOrDefault(int x, int y) {
  if (x < 0 || y < 0) return 0;
  return trees[x][y];
}
 
int main() {
  cin >> dim >> q;
  for (int i = 0; i < dim; i++) {
    cin >> line;
    for (int j = 0; j < dim; j++) {
      int add = 0;
      if (line[j] == '*') add = 1;
      trees[i][j] = getOrDefault(i - 1, j) + getOrDefault(i, j - 1) -
        getOrDefault(i - 1, j - 1) + add;
    }
  }
  for (int i = 0; i < q; i++) {
    cin >> a1 >> b1 >> a2 >> b2; --a1, --b1, --a2, --b2;
    cout << (getOrDefault(a2, b2) - getOrDefault(a1 - 1, b2) - getOrDefault(a2, b1 - 1) +
        getOrDefault(a1 - 1, b1 - 1)) << "\n";
  }
  return 0;
}
