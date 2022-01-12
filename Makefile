run: main

main: graph
	cl main.cpp graph -o main

graph:
	cl graph.cpp -o graph