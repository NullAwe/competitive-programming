#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> arr;

void mvAll(int x, int y) {
  if (x > y) y += n;
  for (int j = y - 1; j >= x; --j) arr.push_back(j % n);
  for (int i = 0; i < (y - x + 1) / 2; ++i) {
    int xx = x + i, yy = y - i;
    for (int j = xx + 1; j < yy; ++j) arr.push_back(j % n);
    for (int j = yy - 2; j >= xx; --j) arr.push_back(j % n);
  }
}

int main() {
  cin >> n;
  mvAll(0, n - 1);
  mvAll((n + 1) / 2, n - 1 - (n + 1) / 2);
  mvAll(0, n - 1);
  cout << arr.size() << '\n';
  for (int num : arr) cout << num << ' ';
  cout << '\n';
  return 0;
}