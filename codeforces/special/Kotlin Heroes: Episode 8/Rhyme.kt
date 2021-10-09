fun main() {
  val t = readLine()?.toIntOrNull() ?: 0
  for (i in 1..t) solve()
}

fun solve() {
  val n = readLine()?.toIntOrNull() ?: 0
  var max = 2147483647
  var min = -1
  // Finds maximum rhyme number for type 0 and minimum rhyme number for type 1:
  for (i in 1..n) {
    var line = readLine()
    if (line == null) line = ""
    var split = line.split(" ").toTypedArray()
    var first = split.elementAt(0)
    var second = split.elementAt(1)
    var type = split.elementAt(2).toInt()
    var biggest = -1
    var to = first.length
    if (second.length < to) to = second.length
    to = to - 1
    for (i in 0..to) {
      if (first.get(first.length - i - 1) != second.get(second.length - i - 1)) {
        biggest = i
        break
      }
    }
    if (biggest < 0) biggest = to + 1   
    if (type == 0 && biggest > min) min = biggest
    else if (type == 1 && biggest < max) max = biggest
  }
  // Output:
  if (min > max) println(0)
  else {
    println(max - min)
    for (i in min + 1..max) {
      print(i)
      print(" ")
    }
	println()
  }
}
