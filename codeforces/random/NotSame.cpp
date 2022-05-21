#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<int>> strs(n + 1, vector<int>(n));
  vector<vector<int>> groups;
  vector<int> og(n + 1); for (int i = 0; i <= n; ++i) og[i] = i;
  groups.push_back(og);
  for (int i = 0; i < n; ++i) {
    vector<vector<int>> newGroups;
    int chosen = 0;
    for (int j = 0; j < groups.size(); ++j) if (groups[j].size() > 1) chosen = j;
    swap(groups[0], groups[chosen]);
    int l = n + 1;
    for (vector<int> group : groups) {
      if (group.size() == 0) continue;
      vector<int> z, o;
      int comp = l == arr[i] ? group.size() : group.size() - 1;
      for (int j = 0; j < min(arr[i], comp); ++j) o.push_back(group[j]), strs[group[j]][i] = 1;
      for (int j = min(arr[i], comp); j < group.size(); ++j) z.push_back(group[j]);
      arr[i] -= min(arr[i], comp);
      l -= group.size();
      newGroups.push_back(z), newGroups.push_back(o);
    }
    groups = newGroups;
  }
  cout << n + 1 << '\n';
  for (vector<int> str : strs) {
    for (int num : str) cout << num;
    cout << '\n';
  }
  return 0;
}
