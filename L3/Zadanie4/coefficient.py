import matplotlib.pyplot as plt
import math

fr = open("Zadanie4/bsearch2.txt", "r") 
 
flogN = open("Zadanie4/log2N.txt", "r") 



comparesR = []
compareslog = []

avgcomparesR = []
avgcompareslog = []
coefficientavg = []


N = []
avgN = []

for x in fr:
    split = x.split()
    comparesR.append(float(split[0]))
fr.close()

for x in flogN:
    split = x.split()
    compareslog.append(float(split[0]))
flogN.close()




for n in range(1000,1000001,1000):
    avgcomR = 0
    avglog = 0
    for k in range(30):
        N.append(n)
        avgcomR += comparesR[int(((n/1000)-1)*30+k)] 
        avglog += compareslog[int(((n/1000)-1)*30+k)]  

    coefficientavg.append(float(avglog/30)/float(avgcomR/30))

coefficient = 0
for c in coefficientavg:
    coefficient += c



coefficient = coefficient/1000

print(coefficient)


