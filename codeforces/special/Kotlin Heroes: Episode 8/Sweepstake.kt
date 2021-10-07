fun main() {
  solve()
}

fun solve() {
  var line = readLine()
  if (line == null) line = ""
  var split = line.split(" ").toTypedArray()
  val n = split.elementAt(0).toInt()
  val m = split.elementAt(1).toInt()
  line = readLine()
  if (line == null) line = ""
  split = line.split(" ").toTypedArray()
  val mx = split.elementAt(0).toInt()
  val my = split.elementAt(1).toInt()
  val x = Array(m - 1, {i -> 0});
  val y = Array(m - 1, {i -> 0});
  for (i in 0..m - 2) {
    line = readLine()
    if (line == null) line = ""
    split = line.split(" ").toTypedArray()
    x[i] = split.elementAt(0).toInt()
    y[i] = split.elementAt(1).toInt()
  }
  val arrX = Array(n + 1, {i -> 0});
  val arrY = Array(n + 1, {i -> 0});
  for (i in 0..m - 2) {
    arrX[x[i]] = arrX[x[i]] + 1
    arrY[y[i]] = arrY[y[i]] + 1
  }
  val arr = Array(n + 1) { IntArray(n + 1) }
  for (i in 0..m - 2) {
    arr[x[i]][y[i]] = arr[x[i]][y[i]] + 1
  }
  var ans = 0
  for (i in 1..n) {
    for (j in 1..n) {
      if (i == j || (i == mx || j == my)) continue
      var tmp = arrX[i] + arrY[j] - arr[i][j]
      if (ans < tmp) ans = tmp
    }
  }
  // Output:
  println(ans + 1)
}
