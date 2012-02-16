# a = m^2 - n^2
# b = 2mn
# c = m^2 + n^2
# a+b+c = 1000; c < 1000 => m/n < sqrt(1000) ~ 32
# for primitive m&n are coprime ie gcd =1 and m-n is odd
# m > n are are natural nos

for n in range(1,32):
  for m in range(n+1,32):
    a = m*m - n*n
    b = 2*m*n
    c = m*m + n*n
    if (a+b+c-1000) == 0:
      print a*b*c
