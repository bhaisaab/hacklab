#Choose n horizontal and n vertical ones, total permutations can be 2n... choose n paths vertically corresponding only 1 horiz will be there..
#2nCn
def ncr(n,r):
  return reduce(lambda x,y:x*y, range(r+1,n+1))/reduce(lambda x,y:x*y, range(1,r+1))

# For every path, one choos
print ncr(20*2, 20)
