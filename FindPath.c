/********************************************************************************* 
* Harman Gidha, hgidha 
* Main File
* FindPath.c 
*********************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[])
{
   FILE *in, *out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      fprintf(stderr, "Error: two arguments needed. Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   int n = 0;
   fscanf(in, "%d", &n);
   Graph g = newGraph(n);

   int x = -1;
   int y = -1;
   fscanf(in, "%d", &x);
   fscanf(in, "%d", &y);
   while(x != 0 && y != 0)
   {
      addEdge(g, x, y);
      fscanf(in, "%d", &x);
      fscanf(in, "%d", &y);
   }

   printGraph(out, g);
   fprintf(out, "\n");

   List l = newList();
   fscanf(in, "%d", &x);
   fscanf(in, "%d", &y);
   while(x != 0 && y != 0)
   {
      clear(l);
      BFS(g, x);
      getPath(l, g, y);
      moveFront(l);
      if(get(l) == NIL)
      {
         fprintf(out, "The distance from %d to %d is infinity\n", x, y);
         fprintf(out, "No %d-%d path exists\n", x, y);
         fprintf(out, "\n");
      }
      else
      {
         fprintf(out, "The distance from %d to %d is %d\n", x, y, length(l) - 1);
         fprintf(out, "A shortest %d-%d path is: ", x, y);
         printList(out, l);
         fprintf(out, "\n");
         fprintf(out, "\n");
      }
      fscanf(in, "%d", &x);
      fscanf(in, "%d", &y);
   }    

   freeList(&l);
   freeGraph(&g);
   fclose(in);
   fclose(out);
   return 0;
}
