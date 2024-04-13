# Bron-Kerbosch-algorithm
Implementation of the Bron-Kerbosch algorithm for finding maximal cliques in an undirected graph. Part of a seminar paper for the course Construction and analysis of algorithms 2.

## Building and running the program
The program is intended to be built and run inside a Linux terminal. To build, use the `make` tool. A `bron_kerbosch` executable should be created in the `bin` directory. To run, use the following command:
```sh
    ./bron_kerbosch <path-to-graph>
```
where `<path-to-graph>` is a path to the graph directory. The graph directory needs to contain a file called `matrix.txt` which contains the adjacency matrix of the graph in the following format:
```sh
<n>
<adj-1-1> <adj-1-2> ... <adj-1-n>
<adj-2-1> <adj-2-2> ... <adj-2-n>
...
<adj-n-1> <adj-n-2> ... <adj-n-n>
```
where `n` is the number of vertices in the graph. Some exaple graph directories are provided in the `assets` directory.
