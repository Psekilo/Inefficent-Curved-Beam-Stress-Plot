import matplotlib.pyplot as plt
import csv

x=[]
y=[]

with open('values.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(float(row[0]))
        y.append(float(row[1]))


plt.plot(x,y, marker='o')

plt.title('curvedbeams.cpp')

plt.xlabel('Radius')
plt.ylabel('Total Stress')

plt.show()