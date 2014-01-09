package main

import "fmt"

func main() {
    //output
    fmt.Println(`testing strings with karat quotes
    in which we can write text with newlines but no escaping of chars like \n or \t`)
    fmt.Println("A regular string with double quotes with escaping \t or \n newline")
    var x string = "hey dude this is a string variable"
    fmt.Println(x)
    fmt.Println(x == "hell yeah")

    //automatic type assignment; A comment, := should have a new variable
    y := "Variable with no explicit type specified"
    fmt.Println(y)
    z := 10
    fmt.Println("Okay this z variable contains the number", z)

    //const
    const u string = "this is a const y string"
    fmt.Println(u)

    //multiple variable definition
    var (
        a = 5
        b = -10
        c = 'd'
    )
    fmt.Println(a,b,c)

    //input
    var input float64
    fmt.Scanf("%f", &input)
    fmt.Println("Floating point you entered was=", input)

    //loops and conditionals
    i := 1
    for i <= 10 {
        fmt.Println(i)
        i += 1
    }
    for i := 1; i <= 10; i++ {
        if i % 3 == 0 {
            fmt.Println("hehe", i)
        }
    }

    //switch-case
    i = 0
    switch i {
        case 0: fmt.Println("Zero")
                        fmt.Println("Just another line in this case")
        default: fmt.Println("Default")
    }

    //arrays
    var t [5]int
    t[4] = 1000
    fmt.Println(t, len(t))

    var total float64 = 0
    for i := 0; i < len(t); i++ {
        total += float64(t[i])
    }
    fmt.Println(total / float64(len(t)))

    //pythonic for loop, _ is the optional interator variable
    for _,value := range t {
        fmt.Println(value)
    }

    //array and shorter syntax
    //v := [5]float64{1,2,3,4,5}
    v := [5]float64{
         1,
         2,
         3,
         4,
         5, // extra trailing , required
    }
    fmt.Println(v)

    //slices: like array, but length can be changed
    var r []int
    r = make([]int, 5, 10) // 10 is the max length of the underlying array
    r[0] = 19
    r[3] = 220
    fmt.Println("r =", r[:3])

    //dynamic length expansion
    r = make([]int, 15)
    r[10] = 100
    fmt.Println("r after expansion =", r)

    //slice functions: append and copy
    slice1 := []int{10,20,30}
    slice2 := append(slice1, 40, 50)
    fmt.Println(slice1, slice2)
    slice3 := []int{1,2,3}
    slice4 := make([]int, 2)
    copy(slice4, slice3) // think, dest = src
    fmt.Println(slice3, slice4)

    //maps: like c++ std::maps or pythonic dict
    var p map[string]int // p is a map of strings to ints
    p = make(map[string]int) //bummer, you've to initialize
    p["kvm"] = 10                        //else you get runtime error
    p["xen"] = 5
    fmt.Println(p)
    delete(p, "kvm") //map,key
    fmt.Println(p)

    //maps: better way to check key,value existence
    value, exists := p["ovm"] // if does not exist, value = 0
    fmt.Println(value, exists)

    //maps: map of strings to map of strings to strings
    issues := map[string]map[string]string{
                                    "kvm": map[string]string{
                                                    "issue": "snapshots",
                                                    "state": "open",
                                    },
                                    "xen": map[string]string{
                                                    "issue": "clustersync",
                                                    "state": "bydesign",
                                    },
    }
    if iss, ok := issues["kvm"]; ok {
        fmt.Println("issue found:", iss["issue"], iss["state"], ok)
    }

    //functions: named return type, panic etc.
    fmt.Println(average([]float64{10,5,10,5,10,5}))

    //functions: multiple returns
    g,h := gh()
    fmt.Println(g, h)

    //functions: variadic functions
    fmt.Println(addv(1,2,3,4))

    //functions: variadic functions passing slice
    sliceargs := []int{1,2,3}
    fmt.Println(addv(sliceargs...))

    //functions: closures
    q := 10
    add := func(x, y int) int {
        return q + x + y
    }
    fmt.Println("closure using q and add:", add(1,1))

    //functions: closures and generators
    makeOddGenerator := func() func() uint {
        i := uint(1)
        return func() (ret uint) {
            ret = i
            i += 2
            return
        }
    }
    nextOdd := makeOddGenerator()
    fmt.Println(nextOdd(), nextOdd(), nextOdd())

    //functions: recursion
    fmt.Println("fac(8) =", fac(8))

    //functions: defer, panic, recover
    f1 := func() {
        fmt.Println("In f1() going to panic")
        //panic("In f1()") //commenting out else anything after f() call won't be executed
    }
    f2 := func() {
        str := recover()
        fmt.Println("In f2(), I should be called at the end of main(); recovered from:", str)
    }
    defer f2()
    f1()

    //pointers: yay!
    zero := func(x *int) {
        *x = 0
    }
    w := 2000
    zero(&w)
    fmt.Println("zero w:", w)

    //pointers: here come new!
    wPtr := new(int)
    zero(wPtr)
    fmt.Println("zero wPtr:", *wPtr)

    //structs and interfaces: pg 100
}

func average(list []float64) (total float64) { //float64 {
    //do a runtime error:
    //panic("Bummer, average is not implemented")
    total = 0.0 //:= 0.0 // if we've named out return type
    for _, v := range list {
        total += v
    }
    //return total / float64(len(list))
    total /= float64(len(list))
    return
}

func gh() (int, int) {
    return 10,11
}

//we could use interface{} if type is not known
func addv(args ...int) int {
    total := 0
    for _, v := range args {
        total += v
    }
    return total
}

func fac(x uint) uint {
    if x < 0 {
        panic("Passing negatives to fac, you kiddin' me")
    }
    if x == 0 {
        return 1
    }
    return x * fac(x-1)
}
