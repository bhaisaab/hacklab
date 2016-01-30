-- Functions

hypotenuse a b = (sqrt (a ^ 2 + b ^ 2))
doubleMe x = x + x
doubleSmallNumber x = (if x > 100 then x else doubleMe x)

-- Lists

[1,2,3] ++ [4,5,6]

"hello" ++ " " ++ "world"

['w','0'] ++ ['0','t']
'H':"ello World"

1:[2,3,4]

"Rohit Yadav" !! 4 -- get's element at index 4, t

head [1,2,3,4] -- returns 1

tail [1,2,3,4] -- returns [2,3,4]

last [1,2,3,4] -- return 4

init [1,2,3,4,5] -- return [1,2,3,4] except the last element

length [1,2,3,4]  -- return 4

null [1,2,3,4] -- return False

null []  -- return True

reverse [1,2,3,4] -- returns [4,3,2,1]

take 3 [1,2,3,4] -- returns [1,2,3]

drop 3 [1,2,3,4,5,6] -- return [4,5,6]

maximum [1,2,3,4] -- return 4
minimum [1,2,3,4] -- return 1
product [1,2,3,4] -- return 24
sum [1,2,3,4] -- return 10

4 `elem` [3,4,5,6] -- return True if element is in the list

[1..10] -- list, [1,2,3... up to 10]
[2,4..20]
[20,19..1]
['a'..'z']
take 10 (cycle [1,2,3])

take 10 (cycle "LOL ")

take 10 (repeat 5)

replicate 3 10 -- returns [10,10,10]

[x*2 | x <- [1..10]]

[x*2 | x <- [1..10], x*2 >= 12]

[ x | x <- [50..100], x `mod` 7 == 3]

boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]

boomBangs [7..20]

[ x | x <- [10..20], x /= 13, x /= 15, x /= 19]

let names = ["human", "scale", "ninja"]
let tlds = [".com", ".io", ".in"]
[n ++ t | n <- names, t <- tlds]

[(1,2),(8,11),(4,5)]

fst (8,10) -- returns 8
snd (8,10) -- return 10

zip [1,2,3,4,5] [5,5,5,5,5]

zip [1..5] ["One", "Two", "Three", "Four", "Five"]

zip [1..] ["apple", "orange", "cherry", "mango"]


