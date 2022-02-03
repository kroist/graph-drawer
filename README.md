# Graph drawer

## Usage
### Installation on Arch Linux
```sh
yay -S graph-drawer
```
### Compilation
```sh
cmake -B build
cmake --build build
```
### Options
| Options | Description |
| --- | --- |
| `--in_json` | Treat input as json object |
| `--in_coords` | Assume that input contains coordinates |
| `--in_file` | Set the name of the input file |
| `--skip_planar` | Skip planarity checking & drawing |
| `--transform` | Choose transformation type (allowed intersections, springs) |
| `--out_type` | Set the output type (allowed normal, json, tikz) |
| `--out_file` | Set the name of the output file |
| `--iterations` | Set the number of iterations |

## Examples
```sh
build/./drawer --in_file examples/0.json --in_json --skip_planar --out_type normal --transform springs
```
```sh
build/./drawer --in_file examples/Goldner_Harary --out_type tikz
```
## Graph formats
Graphs on input are assumed to be connected, undirected and simple.
### Input
* JSON object \
Positions array is optional. Nodes in edges array should be values from *0* to *n-1*.
```js
{
    "size": n,
    "edges": [
        [0, 1],
        ...
    ],
    "positions": [
        [0.5, 12.0],
        ...
    ]
}
```
* normal \
If present (must be specified with `--in_coords` flag), the position list should have length *n*.
```sh
n m
0 1.2 3.0
...
n-1 12.0 1.2
x_1 y_1
...
x_m y_m
```
or, if flag is not not specified:
```sh
n m
x_1 y_1
...
x_m y_m
```