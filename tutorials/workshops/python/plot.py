#
# This example demonstrates how to create charts with Matplotlib.
#

import matplotlib.pyplot as plt
import csv

x  = []
y1 = []
y2 = []

with open('data.csv', 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y1.append(int(row[1]))
        y2.append(int(row[2]))

plt.plot(x, y1, label='First algorithm')
plt.plot(x, y2, label='Second algorithm')

plt.xlabel('Size (N)')
plt.ylabel('Time (milliseconds)')
plt.title('Performance of different algorithms')
plt.legend()
plt.show()
