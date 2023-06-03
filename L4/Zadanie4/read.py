import matplotlib.pyplot as plt
import math

file = open("Zadanie4/fileRANDOM.txt", "r")
heightsinc = open("Zadanie4/decheightsRANDOM.txt", "r")
heightsdec = open("Zadanie4/incheightsRANDOM.txt", "r")



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
    for k in range(1):
        N.append(n)
        avgcom += compares[int(((n/10000)-1)*1+k)] 
        avgpoin += pointers[int(((n/10000)-1)*1+k)]   
        avgmaxcom += maxcompares[int(((n/10000)-1)*1+k)] 
        avgmaxpoin += maxpointers[int(((n/10000)-1)*1+k)]  
    avgcompares.append(float(avgcom/1))
    avgpointers.append(float(avgpoin/1))
    avgmaxcompares.append(float(avgmaxcom/1))
    avgmaxpointers.append(float(avgmaxpoin/1))
    avgN.append(n)



#plt.scatter(N, comparesR, s = 1)

plt.scatter(N, pointers, s = 1)
plt.scatter(avgN,  avgpointers, s = 2, color = 'green')
#plt.scatter(avgN, avgpointers, s = 1, color = 'red')
plt.scatter(avgN, avgmaxpointers, s = 1, color = 'red')
#plt.scatter(avgN, avgmaxpoin, s = 1, color = 'lightgreen')


plt.ylabel('pointers read')
plt.xlabel('n')

plt.show()
