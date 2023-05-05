import matplotlib.pyplot as plt
import math

fdqs = open("Zadanie3/dualqsbign.txt", "r")
fqs = open("Zadanie2/qs/qsbign.txt", "r")

comparesdualQS = []
comparesqs = []
avgcomparesdualQS = []
avgcomparesqs = []

N = []
avgN = []


for x in fdqs:
    split = x.split()
    comparesdualQS.append(float(split[0]))
fdqs.close()

for x in fqs:
    split = x.split()
    comparesqs.append(float(split[0]))
fqs.close()


for n in range(1000,20001,1000):
    
    avgcomkdualQS = 0
    avgcomkqs = 0

    for k in range(10):
        N.append(n)
        avgcomkdualQS += comparesdualQS[int((n-1000)/100+k)]   
        avgcomkqs += comparesqs[int((n-1000)/100+k)]

    avgcomparesdualQS.append(float(avgcomkdualQS/10))
    avgcomparesqs.append(float(avgcomkqs/10))
    avgN.append(n)




plt.scatter(avgN, avgcomparesdualQS, s = 3, color = 'green')
plt.scatter(avgN, avgcomparesqs, s = 3, color = 'red')

plt.ylabel('compares/n')
plt.xlabel('n')

plt.legend([ "dual-pivot qs", "quicksort"])
plt.show()
