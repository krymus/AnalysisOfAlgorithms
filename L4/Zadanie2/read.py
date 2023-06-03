import matplotlib.pyplot as plt
import math

file = open("Zadanie2/fileINC.txt", "r")
heightsinc = open("Zadanie2/decheightsINC.txt", "r")
heightsdec = open("Zadanie2/incheightsINC.txt", "r")



compares = []
avgcompares = []
pointers = []
avgpointers = []
maxcompares = []
avgmaxcompares = []
maxpointers = []
avgmaxpointers = []
heights = []


N = []
avgN = []

for x in file:
    split = x.split()
    compares.append(float(split[0]))
    pointers.append(float(split[1]))
    maxcompares.append(float(split[2]))
    maxpointers.append(float(split[3]))
file.close()

for x in heightsinc:
    split = x.split()
    heights.append(float(split[0]))
heightsinc.close()






for n in range(10000,100001,10000):
    avgcom = 0
    avgpoin = 0
    avgmaxcom = 0
    avgmaxpoin = 0
    for k in range(5):
        N.append(n)
        avgcom += compares[int(((n/10000)-1)*5+k)] 
        avgpoin += pointers[int(((n/10000)-1)*5+k)]   
        avgmaxcom += maxcompares[int(((n/10000)-1)*5+k)] 
        avgmaxpoin += maxpointers[int(((n/10000)-1)*5+k)]  
    avgcompares.append(float(avgcom/5))
    avgpointers.append(float(avgpoin/5))
    avgmaxcompares.append(float(avgmaxcom/5))
    avgmaxpointers.append(float(avgmaxpoin/5))
    avgN.append(n)



#plt.scatter(N, comparesR, s = 1)

plt.scatter(N, compares, s = 1)
plt.scatter(avgN,  avgcompares, s = 2, color = 'green')
#plt.scatter(avgN, avgpointers, s = 1, color = 'red')
plt.scatter(avgN, avgmaxcompares, s = 1, color = 'red')
#plt.scatter(avgN, avgmaxpoin, s = 1, color = 'lightgreen')


plt.ylabel('compares read')
plt.xlabel('n')

plt.show()
