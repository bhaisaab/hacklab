object FP {
    def main(args: Array[String]) {

        def pi = 3.142
        def radius = 10

        // defs are like call by name
        def circumference(r: Double) = (2 * pi) * r
        println("Circumference of circle with r=10 is " + circumference(10))

        def square(x: Double) = x * x
        println("Square 13 = " + square(13))

        // 'x >= 0' is the predicate and it's an expression not statement
        def abs(x: Int) = if(x >= 0) x else -x
        println("Absolute value of -11 is " + abs(-11))

        /* Boolean
          true false -- constants
          !b         -- negation
          b && b     -- conjunction
          b || b     -- disjunction

          comparations; <=, >=, ==, !=, <, >
        */

        // call by value using val
        val x = 2
        def loop(): Boolean = loop()
        //val x = loop would hang

        //Following one will hang for and(true, loop)
        //def and(x: Boolean, y: Boolean) = if(x) y else false
        //Following one has call by name and wont' hang
        def and(x: Boolean, y: => Boolean) = if(x) y else false
        println("and(false, loop) = " + and(false, loop))
    }
}
