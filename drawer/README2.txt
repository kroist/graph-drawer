in this same directory create env with
    python3 -m venv env
do
    source env/bin/ativate

pip install pip install 'networkx[default]'

and then run script with
    ./vizgraph.py

graph format is next


N  (number of nodes)
N lines with coordinates of nodes (x and y)
M (number of edges)
M lines with edges (u and v)

