#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; scanf("%d", &n);
  // Finds vertical and horizontal boundary lines with binary search:
  vector<int> vertical = {0, 0, n, n}, horizontal = {0, 0, n, n};
  int l = 1, r = n + 1;
  while (l < r - 1) {
    int mid = (l + r) / 2;
    printf("? %d %d %d %d\n", mid, 1, n, n);
    fflush(stdout);
    int response; scanf("%d", &response);
    if (response == 0) r = mid;
    else l = mid;
  }
  vertical[0] = l - 1;
  l = 1;
  r = n + 1;
  while (l < r - 1) {
    int mid = (l + r) / 2;
    printf("? %d %d %d %d\n", mid, 1, n, n);
    fflush(stdout);
    int response; scanf("%d", &response);
    if (response == 2) l = mid;
    else r = mid;
  }
  vertical[1] = l - 1;
  l = 0;
  r = n;
  while (l < r - 1) {
    int mid = (l + r) / 2;
    printf("? %d %d %d %d\n", 1, 1, mid, n);
    fflush(stdout);
    int response; scanf("%d", &response);
    if (response == 0) l = mid;
    else r = mid;
  }
  vertical[2] = r;
  l = 0;
  r = n;
  while (l < r - 1) {
    int mid = (l + r) / 2;
    printf("? %d %d %d %d\n", 1, 1, mid, n);
    fflush(stdout);
    int response; scanf("%d", &response);
    if (response == 2) r = mid;
    else l = mid;
  }
  vertical[3] = r;
  l = 1;
  r = n + 1;
  while (l < r - 1) {
    int mid = (l + r) / 2;
    printf("? %d %d %d %d\n", 1, mid, n, n);
    fflush(stdout);
    int response; scanf("%d", &response);
    if (response == 0) r = mid;
    else l = mid;
  }
  horizontal[0] = l - 1;
  l = 1;
  r = n + 1;
  while (l < r - 1) {
    int mid = (l + r) / 2;
    printf("? %d %d %d %d\n", 1, mid, n, n);
    fflush(stdout);
    int response; scanf("%d", &response);
    if (response == 2) l = mid;
    else r = mid;
  }
  horizontal[1] = l - 1;
  l = 0;
  r = n;
  while (l < r - 1) {
    int mid = (l + r) / 2;
    printf("? %d %d %d %d\n", 1, 1, n, mid);
    fflush(stdout);
    int response; scanf("%d", &response);
    if (response == 0) l = mid;
    else r = mid;
  }
  horizontal[2] = r;
  l = 0;
  r = n;
  while (l < r - 1) {
    int mid = (l + r) / 2;
    printf("? %d %d %d %d\n", 1, 1, n, mid);
    fflush(stdout);
    int response; scanf("%d", &response);
    if (response == 2) r = mid;
    else l = mid;
  }
  horizontal[3] = r;
  sort(vertical.begin(), vertical.end());
  sort(horizontal.begin(), horizontal.end());
  vector<pair<int, int>> combs = {{0, 1}, {0, 2}, {0, 3}, {2, 3}, {1, 3}, {1, 2}};
  int cn = 6;
  bool done = false;
  // Finds answer by iterating through all 18 possible cases:
  for (int i = 0; i < cn / 2; ++i) {
    for (int j = 0; j < cn; ++j) {
      // Checks if the rectangles in this case both contain one rectangle:
      int x1 = vertical[combs[i].first] + 1, y1 = horizontal[combs[j].first] + 1,
          x2 = vertical[combs[i].second], y2 = horizontal[combs[j].second];
      if (x1 < 1 || y1 < 1 || x1 > n || y1 > n ||
          x2 < 1 || y2 < 1 || x2 > n || y2 > n ||
          x1 > x2 || y1 > y2) continue;
      printf("? %d %d %d %d\n", x1, y1, x2, y2);
      fflush(stdout);
      int r1; scanf("%d", &r1);
      if (r1 != 1) continue;
      x1 = vertical[combs[(i + 3) % cn].first] + 1;
      y1 = horizontal[combs[(j + 3) % cn].first] + 1;
      x2 = vertical[combs[(i + 3) % cn].second];
      y2 = horizontal[combs[(j + 3) % cn].second];
      if (x1 < 1 || y1 < 1 || x1 > n || y1 > n ||
          x2 < 1 || y2 < 1 || x2 > n || y2 > n ||
          x1 > x2 || y1 > y2) continue;
      printf("? %d %d %d %d\n", x1, y1, x2, y2);
      fflush(stdout);
      int r2; scanf("%d", &r2);
      if (r2 != 1) continue;
      // Checks if all halves of the grid that should contain one rectangle do:
      bool down = (i == 0) || (i == 5) || (vertical[1] == vertical[2]);
      if (vertical[0] != vertical[1]) {
        if (down) printf("? %d %d %d %d\n", 1, 1, vertical[1], n);
        else printf("? %d %d %d %d\n", vertical[1] + 1, 1, n, n);
        fflush(stdout);
        int response; scanf("%d", &response);
        if (response != 1) continue;
      }
      if (vertical[2] != vertical[3]) {
        if (!down) printf("? %d %d %d %d\n", 1, 1, vertical[2], n);
        else printf("? %d %d %d %d\n", vertical[2] + 1, 1, n, n);
        fflush(stdout);
        int response; scanf("%d", &response);
        if (response != 1) continue;
      }
      bool left = (j == 0) || (j == 5) || (horizontal[1] == horizontal[2]);
      if (horizontal[0] != horizontal[1]) {
        if (left) printf("? %d %d %d %d\n", 1, 1, n, horizontal[1]);
        else printf("? %d %d %d %d\n", 1, horizontal[1] + 1, n, n);
        fflush(stdout);
        int response; scanf("%d", &response);
        if (response != 1) continue;
      }
      if (horizontal[2] != horizontal[3]) {
        if (!left) printf("? %d %d %d %d\n", 1, 1, n, horizontal[2]);
        else printf("? %d %d %d %d\n", 1, horizontal[2] + 1, n, n);
        fflush(stdout);
        int response; scanf("%d", &response);
        if (response != 1) continue;
      }
      done = true;
      // Output:
      printf("! %d %d %d %d %d %d %d %d\n", vertical[combs[i].first] + 1, horizontal[combs[j].first] + 1,
          vertical[combs[i].second], horizontal[combs[j].second],
          vertical[combs[(i + 3) % cn].first] + 1, horizontal[combs[(j + 3) % cn].first] + 1,
          vertical[combs[(i + 3) % cn].second], horizontal[combs[(j + 3) % cn].second]);
      break;
    }
    if (done) break;
  }
  return 0;
}
