import random
"""a = list()
i = 1
#b = random.randint(-100, 100)
a.append(-10000)
a.append(-30000)
a.append(40000)
while(len(a)<=5000):
    m = random.randint(-1000000, 1000000)
    n  = 0
    if(m not in a):
            print(i)
            flag = 1
            if(a[i] < a[0]):
                while(flag):
                    m = random.randint(-1000000, 1000000)
                    if(m not in a and m < a[i]):
                        a.append(m)
                        flag = 0
                flag = 1
                while(flag):
                    m = random.randint(-1000000, 1000000)
                    if(m not in a and m > a[i] and m < a[0]):
                        a.append(m)
                        flag = 0
            flag = 1
            if(a[i] > a[0]):
                while(flag):
                    m = random.randint(-1000000, 1000000)
                    if(m not in a and m > a[i]):
                        a.append(m)
                        flag = 0
                flag = 1
                while(flag):
                    m = random.randint(-1000000, 1000000)
                    if(m not in a and m < a[i] and m > a[0]):
                        a.append(m)
                        flag = 0
            i+=1
            """

a = list()
while(len(a)!=100000):
    a.append(random.randint(-100000,100000))

with open("tests_100000.txt.txt", "w") as f:
    for i in a:
        f.write(str(i)+'\n')
