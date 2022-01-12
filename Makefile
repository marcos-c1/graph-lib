run: graph

graph:
	g++ graph.cpp main.cpp -o g && ./g

rm:
	rm *.o