import matplotlib.pyplot as plt
import math

incheights = open("Zadanie4/incheightsRANDOM.txt", "r")
decheights = open("Zadanie4/decheightsRANDOM.txt", "r")



heightsinc = []
heightsdec = []


Ninc = []
Ndec = []


for x in incheights:
    split = x.split()
    heightsinc.append(float(split[0]))
incheights.close()

for x in decheights:
    split = x.split()
    heightsdec.append(float(split[0]))
decheights.close()


for n in range(10000,100001,10000):
    for k in range(1):
        for m in range(n):
            Ninc.append(m)
            Ndec.append(n - m)
        
        
    



#plt.scatter(N, comparesR, s = 1)
#plt.scatter(N, comparesS, s = 1, color = 'red')

plt.scatter(Ninc,  heightsinc, s = 1, color = 'blue')
#plt.scatter(avgN, avgpointers, s = 1, color = 'red')
plt.scatter(Ndec, heightsdec, s = 1, color = 'blue')
#plt.scatter(avgN, avgmaxpoin, s = 1, color = 'lightgreen')


plt.ylabel('height of tree')
plt.xlabel('n')

plt.show()
