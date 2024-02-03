/********************************************************************************* 
* Harman Gidha, hgidha 
* GraphTest.c 
*********************************************************************************/ 

#include "List.h"
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main(int argc, char* argv[])
{
    int n = 10;
    Graph A = newGraph(n);
    Graph B = newGraph(n);
    for(int i = 1; i < n; i++)
    {
        addEdge(A, i, i + 1);
        addEdge(B, i, i + 1);
    }
    printf("Graph A print 1:\n");
    printGraph(stdout, A);
    printf("Graph B print 1:\n");
    printGraph(stdout, B); //Should both be the same
    printf("\n");

    assert(getOrder(A) == getOrder(B));
    assert(getSize(A) == getSize(B));
    assert(getParent(A, 1) == getParent(B, 1));
    assert(getDist(A, 2) == getDist(B, 2));
    
    List ab = newList();
    List bc = newList();
    getPath(ab, A, 2); 
    getPath(bc, B, 2);
    assert(equals(ab, bc));

    BFS(A, 1);
    BFS(B, 1);

    assert(getOrder(A) == getOrder(B));
    assert(getSize(A) == getSize(B));
    assert(getParent(A, 1) == getParent(B, 1));
    assert(getDist(A, 2) == getDist(B, 2));

    makeNull(A);
    makeNull(B);
    
    printf("Graph A print 2:\n");
    printGraph(stdout, A);
    printf("Graph B print 2:\n");
    printGraph(stdout, B); //Should both be the same

    freeList(&ab);
    freeList(&bc);
    freeGraph(&A);
    freeGraph(&B);
    return 0;
}
