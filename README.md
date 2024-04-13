# Bron-Kerbosch-algorithm
Implementation of the Bron-Kerbosch algorithm for finding maximal cliques in an undirected graph. Part of a seminar paper for the course Construction and analysis of algorithms 2.

## Overview
The Bron-Kerbosch algorithm is a method for identifying maximal cliques in an undirected graph. This implementation provides a practical tool for analyzing the clique structure of graphs.

## Building and running the program
### Prerequisites
- Linux environment
- GCC compiler
- GNU Make

### Build instructions
To build the program, navigate to the project directory and use the make tool:
```sh
make
```
This will compile the source code and create an executable named bron_kerbosch in the bin directory.

### Usage
To run the program, execute the following command in a Linux terminal:
```sh
./bin/bron_kerbosch <path-to-graph>
```
where `<path-to-graph>` is a path to the graph directory. The graph directory needs to contain a file called `matrix.txt` which contains the adjacency matrix of the graph.

### Graph representation format
The `matrix.txt` file should adhere to the following format:
```sh
<n>
<adj-1-1> <adj-1-2> ... <adj-1-n>
<adj-2-1> <adj-2-2> ... <adj-2-n>
...
<adj-n-1> <adj-n-2> ... <adj-n-n>
```
where:
- n is the number of vertices in the graph.
- <adj-i-j> represents the edge weight between vertices i and j.
Example graph directories are provided in the `assets` directory.

### Output
Running the program will produce a `results.txt` file in the same directory. This file contains the program output - which consists of time measurements and number of function calls for each of the three implemented Bron-Kerbosch algorithm variants.
