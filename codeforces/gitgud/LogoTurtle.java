import java.io.*;
import java.util.*;

public class WonderRoom {

  private static final int[] DIRS = {-1, 1};
  private static int[][][] memo;

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);
    String commands = in.readLine();
    int n = Integer.parseInt(in.readLine());
    memo = new int[commands.length()][n + 1][2];
    for (int[][] matrix : memo) for (int[] row : matrix) Arrays.fill(row, Integer.MAX_VALUE);
    // Output:
    out.println(Math.max(dp(commands, 0, n, 0), dp(commands, 0, n, 1)));
    out.close();
  }

  private static int dp(String commands, int ind, int change, int dir) {
    if (memo[ind][change][dir] < Integer.MAX_VALUE) return memo[ind][change][dir];
    char com = commands.charAt(ind);
    // Takes care of the special case where we are on the last command:
    if (ind == commands.length() - 1) {
      if (change % 2 == 1) com = com == 'T' ? 'F' : 'T';
      return com == 'F' ? DIRS[dir] : 0;
    }
    int maxDist = Integer.MIN_VALUE;
    // Finds the maximum distance forwards if we don't change the command:
    if (com == 'T') maxDist = dp(commands, ind + 1, change, 1 - dir);
    else maxDist = dp(commands, ind + 1, change, dir) + DIRS[dir];
    // Finds the maximum distance forwards if we do change the command:
    if (change > 0) {
      if (com == 'T') maxDist = Math.max(maxDist, dp(commands, ind + 1, change - 1, dir) + DIRS[dir]);
      else maxDist = Math.max(maxDist, dp(commands, ind + 1, change - 1, 1 - dir));
    }
    memo[ind][change][dir] = maxDist;
    return maxDist;
  }
}
