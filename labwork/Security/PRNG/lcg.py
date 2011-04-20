# Linear Congruential Generator
# Author: Rohit Yadav <rohit.yadav.cse07@itbhu.ac.in>
#         07020003, IDD Part IV, CSE

# xi = (a * xi + x) mod m
# period is atmost m, c!=0, iff:
# 1. c & m are co-primes 
# 2. a-1 is divisible by prime factors of m
# 3. a-1 is multiple of 4 if m is multiple of 4

a = 5
c = 9
m = 16
xi = 0

def seed(x):
    global xi
    xi = x

def rng():
    global xi
    xi = (a*xi + c)%m
    return xi

for i in range(20):
    print rng()
