import matplotlib.pyplot as plt


fq = open("Zadanie5/qs.txt", "r") 
fqS = open("Zadanie5/qsSELECT.txt", "r") 
fdq = open("Zadanie5/dqs.txt", "r") 
fdqS = open("Zadanie5/dqsSELECT.txt", "r") 

comparesq = []
comparesqS = []
comparesdq = []
comparesdqS = []
avgcomparesq = []
avgcomparesqS = []
avgcomparesdq = []
avgcomparesdqS = []

N = []
avgN = []

for x in fq:
    split = x.split()
    comparesq.append(float(split[2]))
fq.close()

for x in fqS:
    split = x.split()
    comparesqS.append(float(split[2]))
fqS.close()

for x in fdq:
    split = x.split()
    comparesdq.append(float(split[2]))
fdq.close()

for x in fdqS:
    split = x.split()
    comparesdqS.append(float(split[2]))
fdqS.close()


for n in range(100,10001,100):
    avgcomq = 0
    avgcomqS = 0
    avgcomdq = 0
    avgcomdqS = 0

    for k in range(30):
        N.append(n)
        avgcomq += comparesq[int(((n/100)-1)*30+k)] 
        avgcomqS += comparesqS[int(((n/100)-1)*30+k)]   
        avgcomdq += comparesdq[int(((n/100)-1)*30+k)]   
        avgcomdqS += comparesdqS[int(((n/100)-1)*30+k)]  

    avgcomparesq.append(float(avgcomq/30))
    avgcomparesqS.append(float(avgcomqS/30))
    avgcomparesdq.append(float(avgcomdq/30))
    avgcomparesdqS.append(float(avgcomdqS/30))
    avgN.append(n)



#plt.scatter(N, comparesR, s = 1)
#plt.scatter(N, comparesS, s = 1, color = 'red')

plt.scatter(avgN, avgcomparesq, s = 1)
plt.scatter(avgN, avgcomparesqS, s = 1, color = 'red')
plt.scatter(avgN, avgcomparesdq, s = 1, color = 'black')
plt.scatter(avgN, avgcomparesdqS, s = 1, color = 'purple')


plt.ylabel('swaps')
plt.xlabel('n')

plt.legend(["QS" , "QSSelect", "DQS", "DQSelect"])
plt.show()
