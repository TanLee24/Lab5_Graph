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
 
Requirements: In class DGraph, implement methods getVertexNode, add and connect. 
Descriptions for each method are provided below. Ensure that all three methods are fully implemented before checking.

Notes: You can use the methods from the previous exercises without needing to implement them again.

For example:

Test	
DGraph<int> graph;
for(int i = 0; i < 6; i++) graph.add(i);
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
Number of edges: 0
==================================================

Test
DGraph<int> graph;
for(int i = 0; i < 6; i++) graph.add(i);

graph.connect(1, 2, 40);
graph.connect(1, 3, 6.9);
graph.connect(4, 5, 27);
graph.connect(3, 2, 2.1);
graph.connect(0, 2, 11.2);
graph.connect(0, 5, 67);
graph.connect(2, 1, 19.75);

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
Number of edges: 7
E(0,2,11.2)
E(0,5,67)
E(1,2,40)
E(1,3,6.9)
E(2,1,19.75)
E(3,2,2.1)
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

template<class T>
typename DGraph<T>::VertexNode* DGraph<T>::getVertexNode(T vertex) 
{
    VertexNode* current = nodeList;
    while (current != nullptr) 
    {
        if (current->vertex == vertex) return current;
        current = current->next;
    }
    return nullptr;
}

template<class T>
void DGraph<T>::add(T vertex) 
{
    // Kiểm tra xem vertex đã tồn tại chưa
    if (getVertexNode(vertex) != nullptr) return; // Không thêm nếu đỉnh đã tồn tại
    
    // Tạo một VertexNode mới
    VertexNode* newNode = new VertexNode(vertex);
    
    // Nếu danh sách rỗng, gán newNode làm đầu danh sách
    if (nodeList == nullptr) 
    {
        nodeList = newNode;
    } 
    else 
    {
        // Tìm phần tử cuối cùng của danh sách
        VertexNode* current = nodeList;
        while (current->next != nullptr) 
        {
            current = current->next;
        }
        // Thêm newNode vào cuối danh sách
        current->next = newNode;
    }
    
    // Tăng số lượng đỉnh
    countVertex++;
}

template <class T>
void DGraph<T>::connect(T from, T to, float weight) 
{
    // Lấy các VertexNode tương ứng với from và to
    VertexNode* fromNode = getVertexNode(from);
    VertexNode* toNode = getVertexNode(to);
     
     // Kiểm tra xem cả hai đỉnh có tồn tại không
    if (fromNode == nullptr || toNode == nullptr) 
        throw VertexNotFoundException("Vertex doesn't exist!");
    
    // Kết nối từ fromNode đến toNode
    bool newEdgeCreated = fromNode->connectTo(toNode, weight);
    
    // Nếu một cạnh mới được tạo, tăng số lượng cạnh
    if (newEdgeCreated) countEdge++;
}