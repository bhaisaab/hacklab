def sumofmultiples(n, rang):
  num = rang/n
  return n * num * (num+1) / 2

print sumofmultiples(3,999)+sumofmultiples(5,999)-sumofmultiples(15,999)
