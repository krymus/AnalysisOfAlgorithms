import matplotlib.pyplot as plt
import math

fmergs = open("Zadanie2/mergs/mergsbign.txt", "r")
fqs = open("Zadanie2/qs/qsbign.txt", "r")

comparesmergs = []
comparesqs = []
avgcomparesmergs = []
avgcomparesqs = []

N = []
avgN = []


for x in fmergs:
    split = x.split()
    comparesmergs.append(float(split[3]))
fmergs.close()

for x in fqs:
    split = x.split()
    comparesqs.append(float(split[3]))
fqs.close()


for n in range(1000,20001,1000):
    
    avgcomkmergs = 0
    avgcomkqs = 0

    for k in range(10):
        N.append(n)
        avgcomkmergs += comparesmergs[int((n-1000)/100+k)]   #    n/10-1+k   k=1    n-10+k   k=10   (n-10)*10+k   k=100
        avgcomkqs += comparesqs[int((n-1000)/100+k)]

    avgcomparesmergs.append(float(avgcomkmergs/10))
    avgcomparesqs.append(float(avgcomkqs/10))
    avgN.append(n)



plt.scatter(avgN, avgcomparesmergs, s = 3, color = 'green')
plt.scatter(avgN, avgcomparesqs, s = 3, color = 'red')

plt.ylabel('swaps/n')
plt.xlabel('n')

plt.legend([ "mergesort", "quicksort"])
plt.show()
