#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
using namespace std;

typedef struct node *adrNode;
typedef struct edge *adrEdge;

struct node {
    string infoVertex;
    adrNode nextVertex;
    adrEdge firstEdge;
};

struct edge {
    string destvertexID;
    int edgeWeight;
    adrEdge nextEdge;
};

struct graph {
    adrNode firstVertex;
};

adrNode createVertex(string newVertex);
adrEdge createEdge(string destVertexID, int weight);
adrNode findVertex(graph G, string vertexID);
adrEdge findEdge(graph G, string sourceVertexID, string destVertexID);
void initGraph(graph &G);
void addVertex(graph &G, string newVertexID);
void addEdge(graph &G, string sourceVertexID, string destVertexID, int weight); //ikut ppt
void deleteVertex(graph &G, string vertexID);
void deleteEdge(graph &G, string sourceVertexID, string destVertexID);
void shortestPath(graph G, string startID, string endID);
void alternativePath(graph G, string startID, string endID, string avoidID);
void buildGraph(graph &G);
void showVertexEdge(graph G);
void showGraph(graph G);
void buildGraph(graph &G);
void printVertexWithMostEdge(graph G);

#endif // GRAPH_H_INCLUDED
