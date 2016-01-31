'a' :: Char
Prelude> :t "alskdfjkl"
"alskdfjkl" :: [Char]
Prelude> :t (True, 'a')
(True, 'a') :: (Bool, Char)
Prelude> :t 4==5
4==5 :: Bool
Prelude> :t 123
123 :: Num a => a
Prelude> :t 123.1
123.1 :: Fractional a => a


addThree :: Int -> Int -> Int -> Int
addThree x y z = x + y + z
Prelude> :t addThree
addThree :: Num a => a -> a -> a -> a


factorial :: Integer -> Integer
factorial n = product [1..n]
-- Int is bounded, Integer is not


circumference :: Float -> Float
circumference r = 2 * pi * r


circumference' :: Double -> Double
circumference' r = 2 * pi * r


Prelude> :t (>)
(>) :: Ord a => a -> a -> Bool
Prelude> compare 1 2
LT
Prelude> compare 1 1
EQ
Prelude> compare 1 0
GT

Prelude> False || read "True"
True
Prelude> 2 - read "3"
-1
Prelude> read "[1,2,3,4]" ++ [3]
[1,2,3,4,3]

-1
Prelude> :t read
read :: Read a => String -> a
Prelude> read "5" :: Int
5
Prelude> read "(3,'a')" :: (Int, Char)
(3,'a')
Prelude> read "(3,\"a\")" :: (Int, [Char])
(3,"a")

Prelude> [LT .. GT]
[LT,EQ,GT]
Prelude> ['a'..'d']
"abcd"
Prelude> ['a' .. 'd']
"abcd"
Prelude> succ 'B'
'C'
Prelude> pred EQ
LT
Prelude> pred 'C'
'B'

Prelude> minBound :: Int
-9223372036854775808
Prelude> maxBound :: Int
9223372036854775807
Prelude> maxBound :: Bool
True
Prelude> minBound :: Bool
False
Prelude> maxBound :: (Bool, Int, Char)
(True,9223372036854775807,'\1114111')
Prelude> minBound :: (Bool, Int, Char)
(False,-9223372036854775808,'\NUL')

