#include <bits/stdc++.h>
#include <communication.h>
using namespace std;

inline void s(int& x, int b, int v) { x -= (x & (1 << b)), x |= v << b; }

void encode(int n, int x) {
  int bits = 1;
  while ((1 << bits) <= n) ++bits;
  set<int> todo; for (int i = 0; i < bits; ++i) todo.insert(i);
  vector<pair<int, int>> same, diff;
  int a = 0, b = 1, l = -1, last = -1;
  while (todo.size() > 1) {
    int b1 = *todo.begin(), b2 = *++todo.begin();
    vector<int> res(4);
    if (b1 == last) res[0] = l;
    else res[0] = send((x >> b1) & 1);
    res[1] = send((x >> b2) & 1);
    res[2] = send((x >> b2) & 1);
    if (res[1] == res[2]) {
      a |= res[1] << b2, b |= res[1] << b2;
      todo.erase(b2);
      l = res[2], last = b2;
      continue;
    }
    res[3] = send((x >> b1) & 1);
    l = res[3], last = b1;
    if (res[0] == res[3]) {
      s(a, b1, res[0]), s(b, b1, res[0]), s(b, b2, 1);
      int taken = 0;
      for (int i = 0; i < same.size() - taken; ++i)
        if (same[i].first == b1)
          swap(same[i], same[same.size() - 1 - taken++]), --i;
      for (int i = 0; i < taken; ++i) {
        s(a, same[same.size() - 1 - i].second, (a >> b1) & 1);
        s(b, same[same.size() - 1 - i].second, (b >> b1) & 1);
      }
      same.resize(same.size() - taken);
      taken = 0;
      for (int i = 0; i < diff.size() - taken; ++i)
        if (diff[i].first == b1)
          swap(diff[i], diff[diff.size() - 1 - taken++]), --i;
      for (int i = 0; i < taken; ++i) {
        s(a, diff[diff.size() - 1 - i].second, 1 - ((a >> b1) & 1));
        s(b, diff[diff.size() - 1 - i].second, 1 - ((b >> b1) & 1));
      }
      diff.resize(diff.size() - taken);
      todo.erase(b1);
    } else {
      int pa = (res[0] == res[1]), pb = 3 - pa;
      if (pa) diff.push_back({b1, b2});
      else same.push_back({b1, b2});
      if (a & (1 << b1)) a |= (pb & 1) << b2;
      else a |= (pa & 1) << b2;
      if (b & (1 << b1)) b |= (pb & 1) << b2;
      else b |= (pa & 1) << b2;
      todo.erase(b2);
    }
  }
}

pair<int, int> decode(int n) {
  int bits = 1;
  while ((1 << bits) <= n) ++bits;
  set<int> todo; for (int i = 0; i < bits; ++i) todo.insert(i);
  vector<pair<int, int>> same, diff;
  int a = 0, b = 1, l = -1, last = -1;
  while (todo.size() > 1) {
    int b1 = *todo.begin(), b2 = *++todo.begin();
    vector<int> res(4);
    if (b1 == last) res[0] = l;
    else res[0] = receive();
    res[1] = receive();
    res[2] = receive();
    if (res[1] == res[2]) {
      a |= res[1] << b2, b |= res[1] << b2;
      todo.erase(b2);
      l = res[2], last = b2;
      continue;
    }
    res[3] = receive();
    l = res[3], last = b1;
    if (res[0] == res[3]) {
      s(a, b1, res[0]), s(b, b1, res[0]), s(b, b2, 1);
      int taken = 0;
      for (int i = 0; i < same.size() - taken; ++i)
        if (same[i].first == b1)
          swap(same[i], same[same.size() - 1 - taken++]), --i;
      for (int i = 0; i < taken; ++i) {
        s(a, same[same.size() - 1 - i].second, (a >> b1) & 1);
        s(b, same[same.size() - 1 - i].second, (b >> b1) & 1);
      }
      same.resize(same.size() - taken);
      taken = 0;
      for (int i = 0; i < diff.size() - taken; ++i)
        if (diff[i].first == b1)
          swap(diff[i], diff[diff.size() - 1 - taken++]), --i;
      for (int i = 0; i < taken; ++i) {
        s(a, diff[diff.size() - 1 - i].second, 1 - ((a >> b1) & 1));
        s(b, diff[diff.size() - 1 - i].second, 1 - ((b >> b1) & 1));
      }
      diff.resize(diff.size() - taken);
      todo.erase(b1);
    } else {
      int pa = (res[0] == res[1]), pb = 3 - pa;
      if (pa) diff.push_back({b1, b2});
      else same.push_back({b1, b2});
      if (a & (1 << b1)) a |= (pb & 1) << b2;
      else a |= (pa & 1) << b2;
      if (b & (1 << b1)) b |= (pb & 1) << b2;
      else b |= (pa & 1) << b2;
      todo.erase(b2);
    }
  }
  return {max(min(a, n), 1), max(min(b, n), 1)};
}
