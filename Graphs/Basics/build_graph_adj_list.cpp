#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct node 
{
	int vertexNum;
	struct node* next;
};

struct llist
{
	struct node* head;	
};

struct Graph
{
	int V;
	int E;
	struct llist* adj_list;
};

struct node* makeNode(int v)
{
	struct node* vertex = new struct node;
	vertex->vertexNum = v;
	vertex->next = NULL;
	return vertex;
}

void add_edge(struct Graph* g, int src, int dest)
{
	// add dest to src list
	struct node* vertex1 = makeNode(dest);
	if(g->adj_list[src].head == NULL)
		g->adj_list[src].head = vertex1;

	else
	{
		vertex1->next = g->adj_list[src].head;
		g->adj_list[src].head = vertex1;
	}

	// add src to dest list
	struct node* vertex2 = makeNode(src);
	if(g->adj_list[dest].head == NULL)
		g->adj_list[dest].head = vertex2;

	else
	{
		vertex2->next = g->adj_list[dest].head;
		g->adj_list[dest].head = vertex2;
	}	
}

void print_graph(struct Graph* g)
{
	int u, v;
	struct node* ptr;

	for(u = 0; u < g->V; u++)
	{
		cout<<"\n"<< u <<": ";
		ptr = g->adj_list[u].head;
		while(ptr != NULL)
		{
			cout<< ptr->vertexNum <<"-->";
			ptr = ptr->next;
		}
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

	// 								method 1
	// g->adj_list = (struct llist*) malloc(g->V * sizeof(struct llist));

	
	// 								method 2 (only for C++)
	g->adj_list = new struct llist [g->V];	// defined number of lists = no. of vertices

	//initialize each list head with NULL
	for(u = 0; u < g->V; u++)
		g->adj_list[u].head = NULL;



	for(i = 0; i < g->E; i++)
	{
		fscanf(reader, "%d %d", &u, &v);
		add_edge(g, u, v);
	}

	print_graph(g);
	fclose(reader);
	return 0;
}