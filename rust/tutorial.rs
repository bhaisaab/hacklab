/* rustc tutorial.rs */

fn is_four(x: int) -> bool {
    x == 4
}

fn main() {
    println!("hello?");

    let mut someVariable : int = 5;
    loop {
        if someVariable < 1 {
            break;
        }
        println!("variable = {}", someVariable);
        someVariable -= 1;
    }

    let mut count = 10;
    while count < 20 {
        println!("count = {}", count);
        count += 1;
    }

    let item = "cloud";
    let price =
        if item == "test" {
            1.30
        } else if item == "cloud" {
            2.00
        } else {
            2.14
        };
    println!("item price = {}", price);
}
