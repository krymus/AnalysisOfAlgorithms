import matplotlib.pyplot as plt
import math

fins = open("Zadanie2/ins/insk1.txt", "r")
fmergs = open("Zadanie2/mergs/mergsk1.txt", "r")
fqs = open("Zadanie2/qs/qsk1.txt", "r")

comparesins = []
comparesmergs = []
comparesqs = []
avgcomparesins = []
avgcomparesmergs = []
avgcomparesqs = []

N = []
avgN = []

for x in fins:
    split = x.split()
    comparesins.append(float(split[3]))
fins.close()

for x in fmergs:
    split = x.split()
    comparesmergs.append(float(split[3]))
fmergs.close()

for x in fqs:
    split = x.split()
    comparesqs.append(float(split[3]))
fqs.close()


for n in range(10,201,10):
    
    avgcomkins = 0
    avgcomkmergs = 0
    avgcomkqs = 0

    for k in range(1):
        N.append(n)
        avgcomkins += comparesins[int(n/10-1+k)]   #    n/10-1+k   k=1    n-10+k   k=10   (n-10)*10+k   k=100
        avgcomkmergs += comparesmergs[int(n/10-1+k)]   
        avgcomkqs += comparesqs[int(n/10-1+k)]

    avgcomparesins.append(float(avgcomkins/1))
    avgcomparesmergs.append(float(avgcomkmergs/1))
    avgcomparesqs.append(float(avgcomkqs/1))
    avgN.append(n)




plt.scatter(avgN, avgcomparesins, s = 3)
plt.scatter(avgN, avgcomparesmergs, s = 3, color = 'green')
plt.scatter(avgN, avgcomparesqs, s = 3, color = 'red')

plt.ylabel('swaps/n')
plt.xlabel('n')

plt.legend(["insertsort" , "mergesort", "quicksort"])
plt.show()
