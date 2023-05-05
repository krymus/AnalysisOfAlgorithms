import matplotlib.pyplot as plt
import math

fs = open("Zadanie4/bsearch2.txt", "r") 
fm = open("Zadanie4/bsearchNby2.txt", "r") 
fe = open("Zadanie4/bsearchN-5.txt", "r") 
fo = open("Zadanie4/bsearchout.txt", "r") 
flog = open("Zadanie4/log2N.txt", "r") 



comparesS = []
comparesM = []
comparesE = []
comparesO = []
compareslog = []
avgcomparesS = []
avgcomparesM = []
avgcomparesE = []
avgcomparesO = []
avgcompareslog = []


N = []
avgN = []

for x in fs:
    split = x.split()
    comparesS.append(float(split[0]))
fs.close()

for x in fm:
    split = x.split()
    comparesM.append(float(split[0]))
fm.close()

for x in fe:
    split = x.split()
    comparesE.append(float(split[0]))
fe.close()

for x in fo:
    split = x.split()
    comparesO.append(float(split[0]))
fo.close()

for x in flog:
    split = x.split()
    compareslog.append(float(split[0]))
flog.close()




for n in range(1000,1000001,1000):
    avgcomS = 0
    avgcomM = 0
    avgcomE = 0
    avgcomO = 0
    avglog = 0
    for k in range(30):
        N.append(n)
        avgcomS += comparesS[int(((n/1000)-1)*30+k)] 
        avgcomM += comparesM[int(((n/1000)-1)*30+k)]   
        avgcomE += comparesE[int(((n/1000)-1)*30+k)]   
        avgcomO += comparesO[int(((n/1000)-1)*30+k)]  
        avglog += compareslog[int(((n/1000)-1)*30+k)]  

    avgcomparesS.append(float(avgcomS/30))
    avgcomparesM.append(float(avgcomM/30))
    avgcomparesE.append(float(avgcomE/30))
    avgcomparesO.append(float(avgcomO/30))
    avgcompareslog.append(float(avglog/30))

    avgN.append(n)



#plt.scatter(N, comparesR, s = 1)
#plt.scatter(N, comparesS, s = 1, color = 'red')

plt.scatter(avgN, avgcomparesS, s = 1)
plt.scatter(avgN, avgcomparesM, s = 1, color = 'red')
plt.scatter(avgN, avgcomparesE, s = 1, color = 'black')
plt.scatter(avgN, avgcomparesO, s = 1, color = 'purple')
plt.scatter(avgN, avgcompareslog, s = 1, color = 'yellow')


plt.ylabel('compares')
plt.xlabel('n')

plt.legend(["Start" , "Middle", "End", "Out", "Log2N"])
plt.show()
