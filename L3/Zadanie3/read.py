import matplotlib.pyplot as plt
import math

f3 = open("Zadanie3/select3M30k80.txt", "r")
f5 = open("Zadanie3/select5M30k80.txt", "r")
f7 = open("Zadanie3/select7M30k80.txt", "r")
f9 = open("Zadanie3/select9M30k80.txt", "r")


compares3 = []
compares5 = []
compares7 = []
compares9 = []
avgcompares3 = []
avgcompares5 = []
avgcompares7 = []
avgcompares9 = []

N = []
avgN = []

for x in f3:
    split = x.split()
    compares3.append(float(split[0]))
f3.close()

for x in f5:
    split = x.split()
    compares5.append(float(split[0]))
f5.close()

for x in f7:
    split = x.split()
    compares7.append(float(split[0]))
f7.close()

for x in f9:
    split = x.split()
    compares9.append(float(split[0]))
f9.close()




for n in range(100,10001,100):
    avgcomk3 = 0
    avgcomk5 = 0
    avgcomk7 = 0
    avgcomk9 = 0
    for k in range(30):
        N.append(n)
        avgcomk3 += compares3[int(((n/100)-1)*30+k)] 
        avgcomk5 += compares5[int(((n/100)-1)*30+k)]   
        avgcomk7 += compares7[int(((n/100)-1)*30+k)]   
        avgcomk9 += compares9[int(((n/100)-1)*30+k)]

    avgcompares3.append(float(avgcomk3/30))
    avgcompares5.append(float(avgcomk5/30))
    avgcompares7.append(float(avgcomk7/30))
    avgcompares9.append(float(avgcomk9/30))
    avgN.append(n)



#plt.scatter(N, comparesR, s = 1)
#plt.scatter(N, comparesS, s = 1, color = 'red')

plt.scatter(avgN, avgcompares3, s = 1)
plt.scatter(avgN, avgcompares5, s = 1, color = 'red')
plt.scatter(avgN, avgcompares7, s = 1, color = 'black')
plt.scatter(avgN, avgcompares9, s = 1, color = 'lightgreen')


plt.ylabel('swaps')
plt.xlabel('n')

plt.legend(["Select3" , "Select5", "Select7" , "Select9"])
plt.show()
