import java.io.*;
import java.util.*;

public class RecyclingBottles {
  public static strictfp void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);
    String[] line = in.readLine().split(" ");
    long ax = Long.parseLong(line[0]), ay = Long.parseLong(line[1]),
        bx = Long.parseLong(line[2]), by = Long.parseLong(line[3]),
        tx = Long.parseLong(line[4]), ty = Long.parseLong(line[5]);
    int n = Integer.parseInt(in.readLine());
    long[][] bottles = new long[n][2];
    for (int i = 0; i < n; i++) {
      line = in.readLine().split(" ");
      bottles[i][0] = Long.parseLong(line[0]);
      bottles[i][1] = Long.parseLong(line[1]);
    }
    // Finds the distance saved to each bottle:
    Bottle[] first = new Bottle[n], second = new Bottle[n];
    for (int i = 0; i < n; i++) {
      first[i] = new Bottle(i, dist(tx, ty, bottles[i][0], bottles[i][1]) -
          dist(ax, ay, bottles[i][0], bottles[i][1]));
      second[i] = new Bottle(i, dist(tx, ty, bottles[i][0], bottles[i][1]) -
              dist(bx, by, bottles[i][0], bottles[i][1]));
    }
    // Sorts the distances by non-increasing order:
    Arrays.sort(first, (b1, b2) -> b1.dist - b2.dist < 0 ? 1 : -1);
    Arrays.sort(second, (b1, b2) -> b1.dist - b2.dist < 0 ? 1 : -1);
    // Takes care of a special case:
    if (n == 1) {
      double dist = dist(tx, ty, bottles[0][0], bottles[0][1]);
      out.println(Math.min(dist + dist(ax, ay, bottles[0][0], bottles[0][1]),
                      dist + dist(bx, by, bottles[0][0], bottles[0][1])));
      out.close();
      return;
    }
    // Computes total walking distance if starting from the recycling bin:
    double dist = 0;
    for (long[] bottle : bottles)
      dist += 2 * dist(tx, ty, bottle[0], bottle[1]);
    // Takes care of another special case where distance actually increases
    // (in this case one person will do all the walking):
    if (first[0].dist < 0 || second[0].dist < 0) {
      out.println(dist - Math.max(first[0].dist, second[0].dist));
      out.close();
      return;
    }
    // Takes care of another special case where the max distance saved for both people
    // is the same bottle:
    if (first[0].id == second[0].id) dist -= Math.max(
              Math.max(first[0].dist + second[1].dist, first[1].dist + second[0].dist),
              Math.max(first[0].dist, second[0].dist));
    else dist -= first[0].dist + second[0].dist; // Normal circumstances.
    // Output:
    out.println(dist);
    out.close();
  }

  private static double dist(long x1, long y1, long x2, long y2) {
    return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  }

  private static class Bottle {

    private final int id;
    private final double dist;

    private Bottle(int id, double dist) {
      this.id = id;
      this.dist = dist;
    }
  }
}
