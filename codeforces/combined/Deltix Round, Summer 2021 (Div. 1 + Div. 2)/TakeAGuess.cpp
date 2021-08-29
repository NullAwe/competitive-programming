#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k; scanf("%d", &n); scanf("%d", &k);
  // Stores the or and and values of adjacent numbers:
  vector<int> _or(n - 1), _and(n - 1);
  for (int i = 1; i < n; ++i) {
    printf("or %d %d\n", i, i + 1);
    fflush(stdout);
    scanf("%d", &_or[i - 1]);
  }
  for (int i = 1; i < n; ++i) {
    printf("and %d %d\n", i, i + 1);
    fflush(stdout);
    scanf("%d", &_and[i - 1]);
  }
  // Stores an or value in case all or/and values are "111..." and "000...":
  int safe = 0;
  printf("or 1 3\n");
  fflush(stdout);
  scanf("%d", &safe);
  int bits = 0;
  for (int num : _or) {
    int bit = 0;
    while (num > 0) {
      ++bit;
      num >>= 1;
    }
    bits = max(bits, bit);
  }
  // Processes bit by bit:
  vector<vector<int>> arr(n, vector<int>(bits, -1));
  for (int i = 0; i < bits; ++i) {
    vector<int> tor(n - 1), tand(n - 1);
    int tsafe;
    for (int j = 0; j < n - 1; ++j) {
      if (_or[j] & (1 << i)) tor[j] = 1;
      else tor[j] = 0;
    }
    for (int j = 0; j < n - 1; ++j) {
      if (_and[j] & (1 << i)) tand[j] = 1;
      else tand[j] = 0;
    }
    if (safe & (1 << i)) tsafe = 1;
    else tsafe = 0;
    for (int j = 0; j < n - 1; ++j)
      if (tor[j] == tand[j]) arr[j][i] = arr[j + 1][i] = tor[j];
    bool has = false;
    for (int j = 0; j < n; ++j) {
      if (arr[j][i] >= 0) {
        has = true;
        break;
      }
    }
    if (!has) arr[0][i] = tsafe;
    for (int j = 0; j < n - 1; ++j) {
      if (tor[j] != tand[j]) {
        if (arr[j][i] >= 0) arr[j + 1][i] = 1 - arr[j][i];
        else if (arr[j + 1][i] >= 0) arr[j][i] = 1 - arr[j + 1][i];
      }
    }
    for (int j = n - 2; j >= 0; --j) {
      if (tor[j] != tand[j]) {
        if (arr[j][i] >= 0) arr[j + 1][i] = 1 - arr[j][i];
        else if (arr[j + 1][i] >= 0) arr[j][i] = 1 - arr[j + 1][i];
      }
    }
  }
  vector<int> sorted(n);
  for (int i = 0; i < n; ++i) {
    int num = 0;
    for (int j = bits - 1; j >= 0; --j) {
      num *= 2;
      num += arr[i][j];
    }
    sorted[i] = num;
  }
  sort(sorted.begin(), sorted.end());
  // Output:
  printf("finish %d\n", sorted[k - 1]);
  return 0;
}