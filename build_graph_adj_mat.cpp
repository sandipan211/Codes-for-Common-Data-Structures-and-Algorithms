#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct Graph
{
	int V;
	int E;
	int **adj_mat;		// 2D matrix
};

void add_edge(struct Graph* g, int src, int dest)
{
	g->adj_mat[src][dest] = g->adj_mat[dest][src] = 1;
}

void print_graph(struct Graph* g)
{
	int u, v;
	for(u = 0; u < g->V; u++)
	{
		cout<<"\n";
		for(v = 0; v< g->V; v++)
			cout<< g->adj_mat[u][v] << " ";
	}
}

int main(int argc, char* argv[])
{
	int i, u, v;
	FILE *reader;
	char filename[50];

	strcpy(filename, argv[1]);

	Graph *g = (Graph*) malloc(sizeof(Graph));
	if(!g)
	{
		cout<<"\nMemory error!";
		return 0;
	}

	reader = fopen(filename, "r");

	fscanf(reader, "%d %d", &g->V, &g->E);

	// allocate memory to graph

	// // 								method 1
	// g->adj_mat = (int**) malloc(g->V * sizeof(int*));
	// for(i = 0; i < g->V; i++)
	// 	g->adj_mat[i] = (int*) malloc(g->V * sizeof(int));
	
	// 								method 2 (only for C++)
	g->adj_mat = new int* [g->V];	// defined number of rows
	for(i = 0; i< g->V; i++)
		g->adj_mat[i] = new int [g->V];

	//initialize adj matrix with zeroes
	for(u = 0; u < g->V; u++)
	{
		for(v = 0; v< g->V; v++)
			g->adj_mat[u][v] = 0;
	}



	for(i = 0; i < g->E; i++)
	{
		fscanf(reader, "%d %d", &u, &v);
		add_edge(g, u, v);
	}

	print_graph(g);
	fclose(reader);
	return 0;
}