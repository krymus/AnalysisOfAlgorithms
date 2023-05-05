import matplotlib.pyplot as plt
import math

fdqs = open("Zadanie3/dualqsbign.txt", "r")

comparesdualQS = []

N = []

for x in fdqs:
    split = x.split()
    comparesdualQS.append(float(split[0]))
fdqs.close()

for n in range(1000,20001,1000):
    for k in range(10):
        N.append(n)
    

constnumbers = []

for n in range(1000,20001,1000):
    for k in range(10):
        constnumbers.append(comparesdualQS[int((n-1000)/100+k)]/N[int((n-1000)/100+k)]/math.log(N[int((n-1000)/100+k)]))

const = 0
for x in constnumbers:
    const+=x

const = const/len(N)
print(const)


