run: graph

graph: 
	g++ graph.cpp utils.cpp main.cpp -o g && ./g

rm:
	rm g