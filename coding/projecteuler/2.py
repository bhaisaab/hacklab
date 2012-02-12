limit = 4000000
i = 1
j = 2
sum=0
while j<limit:
  if j%2==0:
    sum=sum+j
  t=i
  i=j
  j=t+i

print sum
