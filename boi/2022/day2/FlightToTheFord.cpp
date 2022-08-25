#include <bits/stdc++.h>
#include <communication.h>
using namespace std;

inline void s(int& x, int b, int v) { x -= (x & (1 << b)), x |= v << b; }

void encode(int n, int x) {
  set<int> todo; for (int i = 0; i < 30; ++i) todo.insert(i);
  vector<pair<int, int>> same, diff;
  int a = 0, b = 0; b |= 1;
  while (todo.size() > 1) {
    int b1 = *todo.begin(), b2 = *++todo.begin();
    vector<int> res(4);
    res[0] = send((x >> b1) & 1);
    res[1] = send((x >> b2) & 1);
    res[2] = send((x >> b2) & 1);
    res[3] = send((x >> b1) & 1);
    if (res[1] == res[2]) {
      a |= res[1] << b2, b |= res[1] << b2;
      todo.erase(b2);
    } else if (res[0] == res[3]) {
      s(a, b1, res[0]), s(b, b1, res[0]), s(b, b2, 1);
      int cur = b1;
      while (same.size() || diff.size()) {
        pair<int, int> l;
        if (same.size()) {
          for (int i = 0; i < same.size(); ++i) {
            if (same[i].second == cur) {
              swap(same[i], same[same.size() - 1]);
              break;
            }
          }
          l = same.back();
          if (l.second == cur) {
            s(a, l.first, (a >> cur) & 1);
            s(b, l.first, (b >> cur) & 1);
            cur = l.first;
            same.resize(same.size() - 1);
            continue;
          }
        }
        if (!diff.size()) break;
        for (int i = 0; i < diff.size(); ++i) {
          if (diff[i].second == cur) {
            swap(diff[i], diff[diff.size() - 1]);
            break;
          }
        }
        l = diff.back();
        if (l.second != cur) break;
        s(a, l.first, 1 - ((a >> cur) & 1));
        s(b, l.first, 1 - ((b >> cur) & 1));
        cur = l.first;
        diff.resize(diff.size() - 1);
      }
      todo.erase(b1);
    } else {
      int pa = (res[0] == res[1]), pb = 3 - pa;
      if (pa) diff.push_back({b1, b2});
      else same.push_back({b1, b2});
      if (a & (1 << b1)) a |= (pb & 1) << b2;
      else a |= (pa & 1) << b2;
      if (b & (1 << b1)) b |= (pb & 1) << b2;
      else b |= (pa & 1) << b2;
      todo.erase(b1);
    }
  }
}

pair<int, int> decode(int n) {
  set<int> todo; for (int i = 0; i < 30; ++i) todo.insert(i);
  vector<pair<int, int>> same, diff;
  int a = 0, b = 0; b |= 1;
  while (todo.size() > 1) {
    int b1 = *todo.begin(), b2 = *++todo.begin();
    vector<int> res(4);
    for (int i = 0; i < 4; ++i) res[i] = receive();
    if (res[1] == res[2]) {
      a |= res[1] << b2, b |= res[1] << b2;
      todo.erase(b2);
    } else if (res[0] == res[3]) {
      s(a, b1, res[0]), s(b, b1, res[0]), s(b, b2, 1);
      int cur = b1;
      while (same.size() || diff.size()) {
        pair<int, int> l;
        if (same.size()) {
          for (int i = 0; i < same.size(); ++i) {
            if (same[i].second == cur) {
              swap(same[i], same[same.size() - 1]);
              break;
            }
          }
          l = same.back();
          if (l.second == cur) {
            s(a, l.first, (a >> cur) & 1);
            s(b, l.first, (b >> cur) & 1);
            cur = l.first;
            same.resize(same.size() - 1);
            continue;
          }
        }
        if (!diff.size()) break;
        for (int i = 0; i < diff.size(); ++i) {
          if (diff[i].second == cur) {
            swap(diff[i], diff[diff.size() - 1]);
            break;
          }
        }
        l = diff.back();
        if (l.second != cur) break;
        s(a, l.first, 1 - ((a >> cur) & 1));
        s(b, l.first, 1 - ((b >> cur) & 1));
        cur = l.first;
        diff.resize(diff.size() - 1);
      }
      todo.erase(b1);
    } else {
      int pa = (res[0] == res[1]), pb = 3 - pa;
      if (pa) diff.push_back({b1, b2});
      else same.push_back({b1, b2});
      if (a & (1 << b1)) a |= (pb & 1) << b2;
      else a |= (pa & 1) << b2;
      if (b & (1 << b1)) b |= (pb & 1) << b2;
      else b |= (pa & 1) << b2;
      todo.erase(b1);
    }
  }
  return {max(min(a, n), 1), max(min(b, n), 1)};
}
