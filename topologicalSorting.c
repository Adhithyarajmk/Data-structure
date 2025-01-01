#include <stdio.h>
#include <stdlib.h>

// Structure to represent a graph
typedef struct Graph {
    int numVertices;
    int *inDegree;
    int **adjMatrix;
    int **adjList;
} Graph;

// Function to create a graph
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->inDegree = (int*) calloc(numVertices, sizeof(int));
    graph->adjMatrix = (int**) malloc(numVertices * sizeof(int*));
    graph->adjList = (int**) malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjMatrix[i] = (int*) calloc(numVertices, sizeof(int));
        graph->adjList[i] = (int*) malloc(numVertices * sizeof(int));
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjList[src][dest] = 1;
    graph->inDegree[dest]++;
}

// Function to perform DFS traversal
void dfsTraversal(Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && visited[i] == 0) {
            dfsTraversal(graph, i, visited);
        }
    }
}

// Function to perform BFS traversal
void bfsTraversal(Graph* graph, int vertex, int* visited) {
    int* queue = (int*) malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;
    visited[vertex] = 1;
    queue[rear++] = vertex;
    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[v][i] == 1 && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    free(queue);
}

// Function to perform topological sorting
void topologicalSort(Graph* graph) {
    int* queue = (int*) malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[vertex][i] == 1) {
                graph->inDegree[i]--;
                if (graph->inDegree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }
    }
    free(queue);
}

// Function to free the graph
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjMatrix[i]);
        free(graph->adjList[i]);
    }
    free(graph->adjMatrix);
    free(graph->adjList);
    free(graph->inDegree);
    free(graph);
}

// Function to get the number of vertices from the user
int getNumVertices() {
    int numVertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    return numVertices;
}

// Function to get the edges from the user
void getEdges(Graph* graph) {
    int numEdges;
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        printf("Enter the source vertex for edge %d: ", i + 1);
        scanf("%d", &src);
        printf("Enter the destination vertex for edge %d: ", i + 1);
        scanf("%d", &dest);
        addEdge(graph, src, dest);
    }
}

// Example usage
int main() {
    int numVertices = getNumVertices();
    Graph* graph = createGraph(numVertices);
    getEdges(graph);
    printf("DFS Traversal: ");
    int* visited = (int*) calloc(numVertices, sizeof(int));
    for ( (int i = 0; i < numVertices; i++) {
        if (visited[i] == 0) {
            dfsTraversal(graph, i, visited);
        }
    }
    printf("\n");
    printf("BFS Traversal: ");
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < numVertices; i++) {
        if (visited[i] == 0) {
            bfsTraversal(graph, i, visited);
        }
    }
    printf("\n");
    printf("Topological Sorting: ");
    topologicalSort(graph);
    printf("\n");
    free(visited);
    freeGraph(graph);
    return 0;
}
