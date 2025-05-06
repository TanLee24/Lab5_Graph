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
 
Requirements: Implement methods removeEdge and removeVertex. Descriptions for each method are provided below.

Notes:

- The removeTo method is used to delete an edge that ends at the vertex "toNode" from the adjacency list of the current vertex. 
Students should use this method when implementing removeEdge and removeVertex.

- You can use the methods from the previous exercises without needing to implement them again.

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
graph.removeEdge(1, 3);

graph.printGraph();
Result
==================================================
Number of vertices: 6
V(0)
V(1)
V(2)
V(3)
V(4)
V(5)
------------------------------
Number of edges: 1
E(3,2,2.1)
==================================================
Test
DGraph<int> graph;

for(int i = 0; i < 6; i++) graph.add(i);

graph.connect(1, 2, 40);
graph.connect(1, 3, 6.9);
graph.connect(4, 5, 27);
graph.connect(3, 2, 2.1);
graph.connect(1, 2, 11.2);

graph.removeVertex(2);

graph.printGraph();
==================================================
Result
Number of vertices: 5
V(0)
V(1)
V(3)
V(4)
V(5)
------------------------------
Number of edges: 2
E(1,3,6.9)
E(4,5,27)
==================================================

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
#include <stdexcept>

template <class T>
bool DGraph<T>::removeEdge(T from, T to) 
{
    // Lấy các VertexNode tương ứng với from và to
    VertexNode* fromNode = getVertexNode(from);
    VertexNode* toNode = getVertexNode(to);
    
    // Kiểm tra xem cả hai đỉnh có tồn tại không
    if (fromNode == nullptr || toNode == nullptr) 
        throw VertexNotFoundException("Vertex doesn't exist!");
    
    // Xóa cạnh từ fromNode đến toNode bằng removeTo
    bool edgeRemoved = fromNode->removeTo(toNode);
    
    // Nếu cạnh được xóa thành công, giảm countEdge
    if (edgeRemoved) 
    {
        countEdge--;
        return true;
    }
    return false;
}

template <class T>
void DGraph<T>::removeVertex(T removeVertex) 
{
    // Lấy VertexNode tương ứng với removeVertex
    VertexNode* vertexNode = getVertexNode(removeVertex);
    
    // Kiểm tra xem đỉnh có tồn tại không
    if (vertexNode == nullptr)
        throw VertexNotFoundException("Vertex doesn't exist!");
    
    // Duyệt qua tất cả các đỉnh trong nodeList
    VertexNode* current = nodeList;
    while (current != nullptr) 
    {
        // Xóa cạnh từ current đến vertexNode (nếu có)
        if (current != vertexNode && current->removeTo(vertexNode)) 
            countEdge--;
        current = current->next;
    }
    
    // Xóa tất cả các cạnh xuất phát từ vertexNode (adList)
    Edge* edge = vertexNode->adList;
    while (edge != nullptr) 
    {
        Edge* temp = edge;
        edge = edge->next;
        delete temp;
        countEdge--;
    }
    vertexNode->adList = nullptr;
    
    // Xóa vertexNode khỏi nodeList
    if (nodeList == vertexNode) 
    {
        // Nếu vertexNode là đầu danh sách
        nodeList = vertexNode->next;
        delete vertexNode;
    } 
    else 
    {
        // Tìm node trước vertexNode
        current = nodeList;
        while (current != nullptr && current->next != vertexNode) 
        {
            current = current->next;
        }
        if (current != nullptr) 
        {
            current->next = vertexNode->next;
            delete vertexNode;
        }
    }
    
    // Giảm countVertex
    countVertex--;
}