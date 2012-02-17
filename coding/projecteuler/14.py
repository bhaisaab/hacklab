def f(n):
  if n == 1: return 1
  if (n%2) == 0: return n/2
  else: return 3*n+1

dp = {}
def chain(n):
  global dp
  if n in dp:
    return dp[n]
  c = 1
  norg = n
  while n!=1:
    n = f(n)
    if n in dp:
      dp[norg] = c+dp[n]
      return c+dp[n]
    c += 1
  dp[norg] = c
  return c

maxn = 1
for i in range(1,1000000):
  if chain(maxn) < chain(i):
    maxn = i
print maxn, chain(maxn)
