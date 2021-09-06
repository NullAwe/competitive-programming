import java.io.*;
import java.util.*;

public class GreatVovaWall {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);
    int n = Integer.parseInt(in.readLine());
    int[] arr = new int[n];
    String[] line = in.readLine().split(" ");
    for (int i = 0; i < n; i++) arr[i] = Integer.parseInt(line[i]);
    Map<Integer, List<Pair>> intervals = new HashMap<>();
    TreeSet<Integer> inds = new TreeSet<>();
    // Finds all intervals:
    int last = arr[0], num = 1;
    for (int i = 1; i < n; i++) {
      if (arr[i] != last) {
        if (!intervals.containsKey(last)) intervals.put(last, new ArrayList<>());
        intervals.get(last).add(new Pair(i - num, i));
        inds.add(last);
        last = arr[i];
        num = 1;
      } else num++;
    }
    if (!intervals.containsKey(last)) intervals.put(last, new ArrayList<>());
    intervals.get(last).add(new Pair(n - num, n));
    inds.add(last);
    List<Pair> curIntervals = intervals.get(inds.pollFirst());
    while (!inds.isEmpty()) {
      // Checks if all intervals are valid:
      for (Pair pair : curIntervals) {
        if ((pair.b - pair.a) % 2 == 1) {
          // Output:
          out.println("NO");
          out.close();
          return;
        }
      }
      curIntervals.addAll(intervals.get(inds.pollFirst()));
      Collections.sort(curIntervals, (a, b) -> a.a - b.a);
      // Merges connected intervals:
      List<Pair> newIntervals = new ArrayList<>();
      for (Pair pair : curIntervals) {
        if (newIntervals.isEmpty()) newIntervals.add(pair);
        else {
          Pair p = newIntervals.remove(newIntervals.size() - 1);
          if (p.b == pair.a) newIntervals.add(new Pair(p.a, pair.b));
          else {
            newIntervals.add(p);
            newIntervals.add(pair);
          }
        }
      }
      curIntervals = newIntervals;
    }
    // Output:
    out.println("YES");
    out.close();
  }

  private static class Pair {

    private final int a, b;

    private Pair(int a, int b) {
      this.a = a;
      this.b = b;
    }
  }
}
