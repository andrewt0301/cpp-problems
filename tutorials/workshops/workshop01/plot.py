import matplotlib.pyplot as plt
import csv

x  = []
y1 = []
y2 = []
y3 = []

with open('number_mult.csv', 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=';')
    for row in plots:
        x.append(int(row[0]))
        y1.append(int(row[1]))
        y2.append(int(row[2]))
        y3.append(int(row[3]))

plt.plot(x, y1, label='Grade School algorithm')
plt.plot(x, y2, label='Divide And Conquer algorithm')
plt.plot(x, y3, label='Karatsuba algorithm')

plt.xlabel('Size (N)')
plt.ylabel('Time (milliseconds)')
plt.title('Performance of different algorithms')
plt.legend()
plt.show()
