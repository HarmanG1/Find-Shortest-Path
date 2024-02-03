# Find-Shortest-Path

The files all come together to find the shortest path between two elements of a graph using a linked list

## Files

### FindPath.c

FindPath requires two options for an input and output file and finds the shortest path using the graph from Graph.c

- <code>input file</code>: specifies the input file to create the graph and the paths to find.
- <code>output file</code>: specifies the output file for the shortest paths.

### Graph.{c,h}

Contains the source and header files for the Graph ADT implementation

### List.{c,h}

Contains the source and header files for the Linked list ADT implementation

### GraphTest.c

Contains the tests to ensure the function of the Graph ADT from Graph.c

### Makefile

Makefile contains the commands to compile, clean, and leak test the files
