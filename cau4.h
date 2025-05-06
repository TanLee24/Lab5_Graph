/*
Template class DGraph representing a directed graph with type T with the initialized frame. 
It has attribute VertexNode* nodeList, which is the head of a singly linked list, representing list of vertex of this graph.
This class inlcudes 2 classes: VertexNode and Edge.
- Class VertexNode representing a vertex in graph. It has some attributes: 
    + T vertex: the vertex's value.
    + Edge* adList: a singly linked list representing the adjacent edges that have this vertex as their starting vertex (from).
- Class Edge representing an edge in graph. It has some attributes: 
    + VertexNode* fromNode - VertexNode* toNode: represents the starting vertex (from) and ending vertex (to) of this edge.
    + float weight: edge's weight.
 
Requirements: Implement methods shape, empty and clear. Descriptions for each method are provided below.

Notes: You can use the methods from the previous exercises without needing to implement them again.

For example:

Test	
DGraph<int> graph;

for(int i = 0; i < 6; i++) graph.add(i);

graph.connect(1, 2, 40);
graph.connect(1, 3, 6.9);
graph.connect(4, 5, 27);
graph.connect(3, 2, 2.1);
graph.connect(1, 2, 11.2);
graph.connect(1, 3, 67);

graph.removeEdge(1, 2);
graph.removeEdge(4, 5);

cout << graph.shape() << endl;
Result
[Vertices: 6, Edges: 2]

Test
DGraph<int> graph;

for(int i = 0; i < 6; i++) graph.add(i);

graph.connect(1, 2, 40);
graph.connect(1, 3, 6.9);
graph.connect(4, 5, 27);
graph.connect(3, 2, 2.1);
graph.connect(1, 2, 11.2);
graph.connect(1, 3, 67);

graph.clear();
cout << graph.shape() << endl;
cout << (graph.empty() ? "Graph is empty!" : "Graph is not empty!") << endl;
[Vertices: 0, Edges: 0]
Result
Graph is empty!
*/

#include <bits/stdc++.h>
using namespace std;
template <class T>
class DGraph {
public:
     class VertexNode; // Forward declaration
     class Edge; // Forward declaration
protected:
     VertexNode* nodeList; //list of vertexNode of DGraph
     int countVertex;
     int countEdge;
public:
     DGraph() {
          this->nodeList = nullptr;
          this->countEdge = 0;
          this->countVertex = 0;
     }
     ~DGraph() {};
     VertexNode* getVertexNode(T vertex);
     void add(T vertex);
 
     void connect(T from, T to, float weight=0);
 
     void removeVertex(T removeVertex);
     bool removeEdge(T from, T to);
     string shape();
     bool empty();
     void clear();
     void printGraph();

public:
     class VertexNode {
     private:
          T vertex;
          Edge* adList; //list of adjacent edge of this vertex
          VertexNode* next;

          friend class Edge;
          friend class DGraph;
     public:

          VertexNode(T vertex, Edge* adList = nullptr, VertexNode* next = nullptr) {
               this->vertex = vertex;
               this->adList = adList;
               this->next = next;
     }
          string toString();
          void addAdjacentEdge(Edge* newEdge);
          bool connectTo(VertexNode* toNode, float weight = 0);
          bool removeTo(VertexNode* toNode);
          Edge* getEdge(VertexNode* toNode);
     };
 
     class Edge {
     private:
          VertexNode* fromNode;
          VertexNode* toNode;
          float weight;
          Edge* next;

          friend class VertexNode;
          friend class DGraph;
     public:
          Edge(VertexNode* fromNode, VertexNode* toNode, float weight = 0.0, Edge* next = nullptr) {
               this->fromNode = fromNode;
               this->toNode = toNode;
               this->weight = weight;
               this->next = next;
          }
          string toString();

     };
};

//! ANSWER
template<class T>
string DGraph<T>::shape() 
{
    // Tạo chuỗi với định dạng: [Vertices: <numOfVertex>, Edges: <numOfEdge>]
    std::stringstream ss;
    ss << "[Vertices: " << countVertex << ", Edges: " << countEdge << "]";
    return ss.str();
}

template<class T>
bool DGraph<T>::empty() 
{
    // Đồ thị rỗng nếu không có đỉnh và cạnh
    return countVertex == 0 && countEdge == 0;
}

template<class T>
void DGraph<T>::clear() 
{
    // Xóa tất cả các đỉnh và cạnh
    VertexNode* currentVertex = nodeList;
    while (currentVertex != nullptr) 
    {
        // Xóa tất cả các cạnh trong adList của đỉnh hiện tại
        Edge* currentEdge = currentVertex->adList;
        while (currentEdge != nullptr) 
        {
            Edge* tempEdge = currentEdge;
            currentEdge = currentEdge->next;
            delete tempEdge;
        }
        currentVertex->adList = nullptr;
        
        // Xóa đỉnh hiện tại
        VertexNode* tempVertex = currentVertex;
        currentVertex = currentVertex->next;
        delete tempVertex;
    }
    
    // Đặt lại nodeList và các biến đếm
    nodeList = nullptr;
    countVertex = 0;
    countEdge = 0;
}