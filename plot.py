import matplotlib.pyplot as plt

lines = open("data-linear.txt").readlines()
weights = open("weights.txt").readlines()

x_data = []
y_data = []
label = []
for line in lines:
    data = line.strip().split(",")
    x_data.append(float(data[1]))
    y_data.append(float(data[2]))
    label.append(float(data[0]))

wts = []
for weight in weights:
    wts.append(float(weight.strip().split(":")[1]))

x_blue = []
y_blue = []
x_red = []
y_red = []
for i in range(len(x_data)):
    if label[i] == 1.0:
        x_blue.append(x_data[i])
        y_blue.append(y_data[i])
    else:
        x_red.append(x_data[i])
        y_red.append(y_data[i])

# plot points
plt.scatter(x_red, y_red, s=10)
plt.scatter(x_blue, y_blue, s=10)

# plot separator line
y1 = (-wts[0] - wts[1]*(1.0))/wts[2]
y2 = (-wts[0] - wts[1]*(8.0))/wts[2]
plt.plot ([1.0, 8.0], [y1, y2])
plt.savefig("model_plot.png")
plt.show()


