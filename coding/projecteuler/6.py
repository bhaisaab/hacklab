def sum(n):
  return n*(n+1)/2

def square(x):
  return x*x

def sumofsquare(n):
#  sum = 0
#  for i in range(1,n+1):
#    sum += square(i)
#  return sum
  return n*(n+1)*(2*n+1)/6

n = 100
print square(sum(n)) - sumofsquare(n)
