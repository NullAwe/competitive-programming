#include <bits/stdc++.h>
using namespace std;

vector<int> solve(set<int>& arr) {
  if (arr.size() == 0) return vector<int>(0);
  if (arr.size() == 1 && abs(*arr.begin()) < 2) return vector<int>(1, *arr.begin());
  bool has = false;
  for (int num : arr) if (num & 1) has = true;
  if (!has) {
    set<int> next;
    for (int num : arr) next.insert(num / 2);
    vector<int> ans = solve(next);
    for (int i = 0; i < ans.size(); ++i) ans[i] *= 2;
    return ans;
  }
  set<int> nadd;
  for (int num : arr) {
    if ((num & 1) && (num - 1) / 2) nadd.insert((num - 1) / 2);
    else if (num / 2) nadd.insert(num / 2);
  }
  vector<int> ans1 = solve(nadd);
  set<int> nsub;
  for (int num : arr) {
    if ((num & 1) && (num + 1) / 2) nsub.insert((num + 1) / 2);
    else if (num / 2) nsub.insert(num / 2);
  }
  vector<int> ans2 = solve(nsub);
  vector<int> ans = (ans1.size() <= ans2.size() ? ans1 : ans2);
  for (int i = 0; i < ans.size(); ++i) ans[i] *= 2;
  ans.push_back(ans1.size() <= ans2.size() ? 1 : -1);
  return ans;
}

int main() {
  int n; cin >> n;
  set<int> arr;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    if (x) arr.insert(x);
  }
  vector<int> ans = solve(arr);
  cout << ans.size() << '\n';
  for (int num : ans) cout << num << ' ';
  cout << '\n';
}
