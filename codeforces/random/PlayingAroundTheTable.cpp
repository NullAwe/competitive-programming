#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> arr;

inline int getIndex(int row, int val) {
  for (int i = 0; i < n; ++i) if (arr[row][i] == val) return i;
  return -1;
}

inline int dupe(int row) {
  vector<int> count(n);
  for (int num : arr[row]) ++count[num - 1];
  for (int i = 0; i < n; ++i) if (count[i] > 1) return i + 1;
  return 0;
}

inline int check() {
  for (int i = 0; i < n; ++i) if (dupe(i)) return true;
  return false;
}

int main() {
  cin >> n;
  arr = vector<vector<int>>(n, vector<int>(n)); for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> arr[i][j];
  vector<vector<int>> ops;
  while (check()) {
    int start = 0, pass = 0;
    for (int i = 0; i < n; ++i) {
      pass = dupe(i);
      if (pass) {
        start = i;
        break;
      }
    }
    arr[start][getIndex(start, pass)] = 0;
    vector<int> op(n); op[start] = pass;
    for (int i = start + 1; i < start + n; ++i) {
      int row = i % n;
      pass = dupe(row);
      if (!pass) pass = op[(i - 1) % n];
      arr[row][getIndex(row, pass)] = 0;
      arr[row][getIndex(row, 0)] = op[(i - 1) % n];
      op[row] = pass;
    }
    arr[start][getIndex(start, 0)] = pass;
    ops.push_back(op);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      vector<int> op(n);
      for (int k = i - j + n + 1; k < i - j + n + 1 + n; ++k) op[k - i + j - n - 1] = (k - 1) % n + 1;
      ops.push_back(op);
    }
  }
  cout << ops.size() << '\n';
  for (vector<int> op : ops) {
    for (int move : op) cout << move << ' ';
    cout << '\n';
  }
  return 0;
}
