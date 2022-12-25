import matplotlib.pyplot as plt
fd = open("test.txt", "r")
file = fd.read()
file = file.replace(".000000", "")
file = file.split()
