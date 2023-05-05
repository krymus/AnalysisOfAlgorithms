import matplotlib.pyplot as plt
import math

fr= open("Zadanie2/rselectM30k5.txt", "r")
fs = open("Zadanie2/selectM30k5.txt", "r")


comparesR = []
comparesS= []
avgcomparesR= []
avgcomparesS = []

N = []
avgN = []

for x in fr:
    split = x.split()
    comparesR.append(float(split[1]))
fr.close()

for x in fs:
    split = x.split()
    comparesS.append(float(split[1]))
fs.close()




for n in range(100,10001,100):
    avgcomkR = 0
    avgcomkS = 0
    for k in range(30):
        N.append(n)
        avgcomkR += comparesR[int(((n/100)-1)*30+k)]   #    n/10-1+k   k=1    n-10+k   k=10   (n-10)*10+k   k=100
        avgcomkS += comparesS[int(((n/100)-1)*30+k)]   

    avgcomparesR.append(float(avgcomkR/30))
    avgcomparesS.append(float(avgcomkS/30))
    avgN.append(n)



#plt.scatter(N, comparesR, s = 1)
#plt.scatter(N, comparesS, s = 1, color = 'red')

plt.scatter(avgN, avgcomparesR, s = 1)
plt.scatter(avgN, avgcomparesS, s = 1, color = 'red')


plt.ylabel('swaps')
plt.xlabel('n')

plt.legend(["RandomizedSelect" , "Select"])
plt.show()
