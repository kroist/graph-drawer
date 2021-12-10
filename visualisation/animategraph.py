#!env/bin/python3
import networkx as nx
import matplotlib.pyplot as plt
import sys
from matplotlib import animation
import numpy as np


if len(sys.argv) < 2:
    print("specify filename as argument!")
    exit(1)

filename = sys.argv[1]

node_size=300
if len(sys.argv) > 2:
    node_size = int(sys.argv[2])



f = open(filename, 'r')


n, m = [int(x) for x in next(f).split()]

g = nx.Graph()
g.add_nodes_from([x for x in range(n)])

poses = []

MAXRAND = 1000
ITER = 10000
rate = 0.0001
cRep = 2
cSpring = 10
sLen = 1


for i in range(n):
    poses.append(np.random.randint(MAXRAND, size=2).astype('float64'))

matr = np.zeros((n, n))

for i in range(m):
    a, b = [int(x) for x in next(f).split()]
    g.add_edge(a, b)
    matr[a][b] = matr[b][a] = 1
f.close()

def dist(a, b):
    return np.sqrt((a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]))

def fSpring(a, b):
    return cSpring * np.log(dist(a, b)/sLen)

def fRep(a, b):
    return cRep / (dist(a, b)*dist(a, b))

def displacement(v, n, matr, coords):
    res = np.array([0, 0], dtype='float64')
    for i in range(n):
        if i == v:
            continue
        if matr[v][i] == 1:
            k = fSpring(coords[i], coords[v])
            cur = coords[i] - coords[v]
            res += k*cur
        else:
            k = fRep(coords[i], coords[v])
            cur = coords[v]-coords[i]
            res += k*cur
    return res



def update(num, n, G, ax):
    ax.clear()
    dsp = []
    for i in range(n):
        dsp.append(displacement(i, n, matr, poses))
    for i in range(n):
        poses[i] += rate*dsp[i]
    pos = {}

    for i in range(n):
        pos[i] = poses[i]

    nx.draw(G, pos=pos, ax=ax, node_size=node_size)





#nx.draw(g, pos=pos, node_size=node_size)
plt.axis('square')

fig = plt.figure()
ax = plt.axes()
fig, ax = plt.subplots(figsize=(6, 4))

ani = animation.FuncAnimation(fig, update, frames=ITER, interval=1, fargs=(n, g, ax))


plt.show()


