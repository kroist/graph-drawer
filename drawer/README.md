in this same directory create env with
    `python3 -m venv env`
do
    `source env/bin/ativate`

    `pip install -r requirements.txt`

and then run script with
    `./vizgraph.py`

graph file format is next:

- N  (number of nodes)
- N lines with coordinates of nodes (x and y)
- M (number of edges)
- M lines with edges (u and v)

