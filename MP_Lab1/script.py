import matplotlib.pyplot as plt
fd = open("test.txt", "r")
file = fd.read()
file = file.replace(".000000", "")
file = file.split()
osi = range(0,1)
plt.plot((1,2,3,4,5,6,7,8), osi)
plt.show()
