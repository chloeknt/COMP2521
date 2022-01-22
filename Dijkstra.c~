// Dijkstra API implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dijkstra.h"
#include "Graph.h"
#include "PQ.h"

int minDistance(Graph g, int dist[], bool sptSet[]);
void printSolution(Graph g, int dist[]);
static bool incomplete(Graph g, bool sptSet[]);
static int weight(Graph g, int u, int v);
static void addPQ(Graph g, PQ pq, int u);
static bool isValid(Graph g, ShortestPaths sps, int u, int v, bool sptSet[]);
static PredNode *newNode(Graph g, ShortestPaths sps, int u, int v, bool sptSet[]);
void showShortestPaths(ShortestPaths sps);
static bool doesntExist(ShortestPaths sps, int v, int u);

ShortestPaths dijkstra(Graph g, Vertex src) {
    // New shortest path struct
    ShortestPaths sps;
    sps.src = src;
    sps.numNodes = GraphNumVertices(g);
    sps.dist = malloc(sizeof(int) * GraphNumVertices(g));
    sps.pred = malloc(sizeof(PredNode*) * GraphNumVertices(g));
    // Keep track of added vertexes
    bool sptSet[GraphNumVertices(g)];
    //Initialising all arrays
    for (int i = 0; i < GraphNumVertices(g); i++) {
        sps.pred[i] = NULL;
        sps.dist[i] = INFINITY;
        sptSet[i] = false;
    }
    // Filling in src info
    PQ pq = PQNew();
    PQInsert(pq, src, 0);
    sps.dist[src] = 0;
    sptSet[src] = true;
    int u;
    // Loop through the vertexes and fill arrays
    while (!PQIsEmpty(pq)) {
        u = PQDequeue(pq);
        for (int v = 0; v < GraphNumVertices(g); v++) {
            // If the path is valid, set pred and dist 
            if (isValid(g, sps, u, v, sptSet)) {
                sps.pred[v] = newNode(g, sps, u, v, sptSet);
                sps.dist[v] = sps.dist[u] + weight(g, u, v);
                if (incomplete(g, sptSet)) {
                    addPQ(g, pq, v);
                    sptSet[v] = true;
                }
            }
        }
    }

    PQFree(pq);
    return sps;
}

// Function determines if the sptSet array is incomplete
static bool incomplete(Graph g, bool sptSet[]) {
    for (int i = 0; i < GraphNumVertices(g); i++) {
        if (!sptSet[i]) {
            return true;
        }
    }
    return false;
}

// Function determines if the path u->v is valid based on criteria 
static bool isValid(Graph g, ShortestPaths sps, int u, int v, bool sptSet[]) {
    // Has to be adjacent
    if (!GraphIsAdjacent(g, u, v)) {
        return false;
    }
    // The distance cannot equal infinity
    if (sps.dist[u] == INFINITY) {
        return false;
    }
    // The added new distance cannot be larger than the pre-existing distance 
    if (sps.dist[u] + weight(g, u, v) > sps.dist[v]) { 
        return false;
    }
    return true;
}

// Function adds a new node onto the pred array depending on circumstances
static PredNode *newNode(Graph g, ShortestPaths sps, int u, int v, bool sptSet[]) {
    // If there are no preds so far for v
    if (!sptSet[v]) {
        PredNode *new = malloc(sizeof(PredNode));
        new->v = u;
        new->next = NULL;
        return new;
        // Already at least one pred and lower dist value, replace the list
    } else if (sps.dist[u] + weight(g, u, v) < sps.dist[v]) {
        PredNode *curr = sps.pred[v];
        PredNode *temp = NULL;
        while (curr != NULL) {
            temp = curr;
            curr = curr->next;
            free(temp);
        }
        PredNode *new = malloc(sizeof(PredNode));
        new->v = u;
        new->next = NULL;
        return new;
        // Already a pred and equal dist
    } else {
        if (doesntExist(sps, v, u)) {
            PredNode *new = malloc(sizeof(PredNode));
            new->v = u;
            new->next = NULL;
            PredNode *curr = sps.pred[v];
            PredNode *prev = NULL;
            while (curr != NULL) {
                prev = curr;
                curr = curr->next;
            }
            prev->next = new;
        } 
        PredNode *root = sps.pred[v];
        return root;
    }
}

// Function determines if the vertex already exists in the pred list
static bool doesntExist(ShortestPaths sps, int v, int u) {
    PredNode *curr = sps.pred[v];
    while (curr != NULL) {
        if (curr->v == u) {
            return false;
        }
        curr = curr->next;
    }
    return true;
}

// Function adds all the edges outgoing u to PQ
static void addPQ(Graph g, PQ pq, int u) {
    for (int i = 0; i < GraphNumVertices(g); i++) {
        if (GraphIsAdjacent(g, u, i)) {
            PQInsert(pq, u, weight(g, u, i));
        }
    }
}

// Function returns the weight of path u -> v
static int weight(Graph g, int u, int v) {
    AdjList curr = GraphOutIncident(g, u);
    // Find the vertex
    while (curr != NULL) {
        if (v == curr->v) {
            break;
        }
        curr = curr->next;
    }
    return curr->weight;
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(Graph g, int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX;
    int min_index;
 
    for (int v = 0; v < GraphNumVertices(g); v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(Graph g, int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < GraphNumVertices(g); i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void showShortestPaths(ShortestPaths sps) {
    
}

// Frees the shortest path struct 
void freeShortestPaths(ShortestPaths sps) {
    // Free dist array
    free(sps.dist);
    // Free pred array
    for (int i = 0; i < sps.numNodes; i++) {
        PredNode *curr = sps.pred[i];
        PredNode *temp = NULL;
        while (curr != NULL) {
            temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
}


