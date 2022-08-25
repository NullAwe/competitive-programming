#include <bits/stdc++.h>
#include <art.h>
using namespace std;

void solve(int n) {
  vector<int> arr(n), order(n); for (int i = 0; i < n; ++i) arr[i] = i + 1;
  set<int> un; for (int i = 0; i < n; ++i) un.insert(i);
  int base = publish(arr);
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < i; ++j) arr[j] = j + 1;
    for (int j = i; j < n - 1; ++j) arr[j] = j + 2;
    arr[n - 1] = i + 1;
    int comp = publish(arr), l = (base - comp + n - i - 1) / 2, rem = 0;
    for (int num : un) {
      if (rem == l) {
        rem = num;
        break;
      }
      ++rem;
    }
    order[rem] = i + 1, un.erase(rem);
  }
  for (int i = 0; i < n; ++i) if (!order[i]) order[i] = n;
  answer(order);
}
