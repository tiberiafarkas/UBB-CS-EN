"""
Illustrate that sum ( (-1)^(n+1)/n ) = ln 2 by computing partial sums   = 1 - 1/2  + 1/3 - ...
                n>=1

Change the order of summation in this series – for example by first adding p positive terms,
then q negative terms, and so on – and show numerically that the rearrangement gives a
different sum (depending on p, q).

"""

n = 1000
sum = []
sum.append(0)

#value of ln2 = 0,69314718055994530941723212145818

for i in range(1, n+1):
    value = (-1) ** ( i + 1 ) / i
    sum.append(sum[-1] + value)
    print(f"The sum of first {i} terms is:", sum[i])

new_sum = []
new_sum.append(0)

print('\n')

p = int(input("Enter the number of first p positive terms you want to add: "))
q = int(input("Enter the number of first q negative terms you want to add: "))

j = 1
for i in range(p):
    value = 1 / j
    new_sum.append(new_sum[-1] + value)
    print(f"The sum of first {i} positive terms is:", new_sum[i])
    j += 2

j = 2
for i in range(q):
    value = -1 / j
    new_sum.append(new_sum[-1] + value)
    print(f"The sum of first {p+i} terms is:", new_sum[p+i])
    j += 2