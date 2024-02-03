/********************************************************************************* 
* Harman Gidha, hgidha 
* Graph.c 
*********************************************************************************/ 

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct GraphObj{
   List *Neigh; //An array of Lists whose ith element contains the neighbors of vertex i.
   int *color; //An array of ints (or chars, or strings) whose ith element is the color (white, gray, black) of vertex i
   int *parent; //An array of ints whose ith element is the parent of vertex i.
   int *dist; //An array of ints whose ith element is the distance from the (most recent) source to vertex i.
   int order; //number of vertices 
   int size; //number of edges
   int source;
} GraphObj;

Graph newGraph(int n)
{
   Graph g;
   g = malloc(sizeof(GraphObj));
   assert(g!=NULL);
   g->order = n;
   g->size = 0;
   g->Neigh = calloc(n+1, sizeof(List));
   g->color = calloc(n+1, sizeof(int));
   g->parent = calloc(n+1, sizeof(int));
   g->dist = calloc(n+1, sizeof(int));
   g->source = NIL;
   for(int i = 1; i <= n; i++)
   {
      g->Neigh[i] = newList();
      g->color[i] = White;
      g->parent[i] = NIL;
      g->dist[i] = INF;
   }
   return g;
}

void freeGraph(Graph* pG)
{
   if(pG != NULL && *pG != NULL)
   {
      for(int i = 0; i <= (*pG)->order; i++)
      {
         freeList(&(*pG)->Neigh[i]);
      }
      free((*pG)->Neigh);
      free((*pG)->color);
      free((*pG)->parent);
      free((*pG)->dist);
      free((*pG));
      *pG = NULL;
   }
}

int getOrder(Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   return G->order;
}

int getSize(Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   return G->size;
}

int getSource(Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   return G->source;
}

int getParent(Graph G, int u)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(getSource(G) == NIL)
   {
      return NIL;
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   return G->parent[u];
}

int getDist(Graph G, int u)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(getSource(G) == NIL)
   {
      return INF;
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   return G->dist[u];
}

void getPath(List L, Graph G, int u)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   if(u == G->source) 
   {
      append(L, u);
   }
   else if (G->parent[u] == NIL) 
   {
      append(L, NIL);
   }
   else
   {
      getPath(L, G, G->parent[u]);
      append(L, u);
   }
}

void makeNull(Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   for(int i = 1; i <= G->order; i++)
   {
      clear(G->Neigh[i]);
      G->color[i] = White;
      G->dist[i] = INF;
      G->parent[i] = NIL;
   }
   G->size = 0;
}

void addEdge(Graph G, int u, int v)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   if(v < 1 ||v > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for v not met\n");
      exit(EXIT_FAILURE);
   }
   addArc(G, u, v);
   addArc(G, v, u);
   G->size = G->size - 1;
}

void addArc(Graph G, int u, int v)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   if(v < 1 ||v > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for v not met\n");
      exit(EXIT_FAILURE);
   }
   bool inserted = false;
   moveFront(G->Neigh[u]);
   while(!inserted)
   {
      if(index(G->Neigh[u]) == -1)
      {
         append(G->Neigh[u], v);
         inserted = true;
      }
      else if(v < get(G->Neigh[u]))
      {
         insertBefore(G->Neigh[u], v);
         inserted = true;
      }
      else
      {
         moveNext(G->Neigh[u]);
      }
   }
   G->size+= 1;
}

void BFS(Graph G, int s)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   G->source = s;
   for(int x = 0; x <= G->order; x++)
   {
      G->color[x] = White;
      G->dist[x] = INF;
      G->parent[x] = NIL;
   }
   G->color[s] = Gray;       
   G->dist[s] = 0;
   G->parent[s] = NIL;
   List Q = newList();
   append(Q, s);
   while(length(Q) > 0)
   {
      int x = front(Q);
      deleteFront(Q);
      moveFront(G->Neigh[x]);
      while(index(G->Neigh[x]) != -1)
      {
         int y = get(G->Neigh[x]);
         if(G->color[y] == White)
         {
            G->color[y] = Gray;
            G->dist[y] = G->dist[x] + 1;
            G->parent[y] = x;
            append(Q, y);
         }
         moveNext(G->Neigh[x]);
      }
      G->color[x] = Black;
   }
   freeList(&Q);
}

void printGraph(FILE* out, Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   for(int i = 1; i <= G->order; i++)
   {
      fprintf(out, "%d: ", i);
      printList(out, G->Neigh[i]);
      fprintf(out, "\n");
   }
}
