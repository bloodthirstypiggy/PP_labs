import matplotlib.pyplot as plt
fd = open("test.txt", "r")
for line in fd:
    plt.plot(int(line))

