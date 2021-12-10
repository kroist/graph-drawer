#!env/bin/python3
import networkx as nx
import matplotlib.pyplot as plt
import sys


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

pos = {}
for i in range(n):
    c, a, b = [float(x) for x in next(f).split()]
    pos[i] = [a, b]

for i in range(m):
    a, b = [int(x) for x in next(f).split()]
    g.add_edge(a, b)

nx.draw(g, pos=pos, node_size=node_size)
plt.axis('square')
plt.show()


f.close()
