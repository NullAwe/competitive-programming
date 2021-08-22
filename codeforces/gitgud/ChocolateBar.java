import java.io.*;

public class ChocolateBar {

  private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
  private static PrintWriter out = new PrintWriter(System.out);
  private static int[][][] memo;

  public static void main(String[] args) throws IOException {
    memo = new int[31][31][51];
    int t = Integer.parseInt(in.readLine());
    for (int i = 0; i < t; i++) solve();
    out.close();
  }

  private static void solve() throws IOException {
    String[] line = in.readLine().split(" ");
    // Output:
    out.println(dp(Integer.parseInt(line[0]), Integer.parseInt(line[1]), Integer.parseInt(line[2])));
  }

  private static int dp(int n, int m, int k) {
    if (k == 0 || n * m == k) return 0;
    if (memo[n][m][k] > 0) return memo[n][m][k];
    int min = Integer.MAX_VALUE;
    // Slicing parallel to the side with length m:
    for (int i = 1; i < n; i++) {
      if (i <= k / m) min = Math.min(min, dp(n - i, m, k - k / m * m) + m * m);
      else min = Math.min(min, dp(i, m, k) + m * m);
    }
    // Slicing parallel to the side with length n:
    for (int i = 1; i < m; i++) {
      if (i <= k / n) min = Math.min(min, dp(n, m - i, k - k / n * n) + n * n);
      else min = Math.min(min, dp(n, i, k) + n * n);
    }
    memo[n][m][k] = min;
    return memo[n][m][k];
  }
}
