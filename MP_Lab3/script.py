import matplotlib.pyplot as plt
fd = open("result.txt", "r")
file = fd.read()
file = file.split()
file = list(file)
file = [float(item) for item in file]
plt.subplot(1,3,1) #working time: 1.1 0.8 0.6 0.4
plt.plot([1,2,3,4,5,6,7,8], file)
plt.title('working time')
newfile = []
for i in range (1,9):
    newfile.append(float(file[0]/i))
plt.plot([1,2,3,4,5,6,7,8], newfile, 'g--')
plt.xlabel('threads')
plt.ylabel('time')
plt.subplot(1,3,2)
velocity = [] # veolcity: 1.1 / 0.8 ; 1.1 / 0.6
for i in range (0,8):
    velocity.append(float(file[0]/file[i]))
print(velocity)
plt.plot([1,2,3,4,5,6,7,8], velocity)
plt.title('velocity')
plt.xlabel('threads')
plt.ylabel('number')
plt.subplot(1,3,3)
effectiveness = []
for i in range (0,8):
    effectiveness.append(float(velocity[i]/(i+1)))

plt.xlabel('threads')
plt.ylabel('efficiency')
plt.title('efficiency')
plt.plot([1,2,3,4,5,6,7,8], effectiveness)
plt.show()


