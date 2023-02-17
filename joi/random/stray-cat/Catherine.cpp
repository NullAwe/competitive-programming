#include "Catherine.h"
#include <bits/stdc++.h>
using namespace std;

int a;

void Init(int _a, int _b) {
  a = _a;
}

int prv = -1;
bool start = false;
vector<int> seen;

bool forwards() {
  vector<int> f1 = {0, 1, 0, 0, 1};
  vector<int> f2 = {1, 0, 0, 1, 1};
  vector<int> f3 = {0, 0, 1, 1, 0};
  vector<int> f4 = {0, 1, 1, 0, 1};
  vector<int> f5 = {1, 1, 0, 1, 0};
  vector<int> f6 = {1, 0, 1, 0, 0};
  return seen == f1 || seen == f2 || seen == f3 || seen == f4 || seen == f5 || seen == f6;
}

int Move(vector<int> y) {
  vector<int> copy = y;
  y.clear();
  for (int i = 0; i < copy.size(); ++i)
    for (int j = 0; j < copy[i]; ++j) y.push_back(i);
  if (a == 2) {
    if (start) {
      if (y.size() == 1) {
        return prv = y[0];
      }
      for (int i = 0; i < y.size(); ++i) {
        if (y[i] != prv) {
          return prv = y[i];
        }
      }
      return 0;
    } else {
      if (y.size() > 1) {
        int sum = 0;
        for (int num : y) sum += num;
        if (prv == -1 && y.size() == 2) {
          seen.push_back(y[0]), seen.push_back(y[1]);
          return prv = y[1];
        }
        if (sum == 0 || sum == y.size()) {
          start = true;
          return -1;
        }
        if (prv == -1) {
          int find = sum == 1;
          for (int i = 0; i < y.size(); ++i) {
            if (y[i] == find) {
              start = true;
              return prv = y[i];
            }
          }
          return 0;
        }
        for (int i = 0; i < y.size(); ++i) {
          if (y[i] != prv) {
            start = true;
            return prv = y[i];
          }
        }
        return 0;
      } else {
        if (y.size() == 0) {
          start = true;
          return -1;
        }
        seen.push_back(y[0]);
        if (seen.size() < 5) {
          return prv = y[0];
        }
        start = true;
        if (forwards()) {
          return prv = y[0];
        }
        return -1;
      }
      return 0;
    }
  }
  vector<int> count(3);
  for (int num : y) ++count[num];
  if (max(count[0], max(count[1], count[2])) == y.size()) return y[0];
  return !count[0] ? 1 : (!count[1] ? 2 : 0);
}
