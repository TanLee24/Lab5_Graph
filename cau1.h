/*
Template class DGraph representing a directed graph with type T with the initialized frame. 
It has attribute VertexNode* nodeList, which is the head of a singly linked list, representing a list of vertex of this graph.
This class inlcudes 2 classes: VertexNode and Edge.
- Class VertexNode representing a vertex in graph. It has some attributes: 
    + T vertex: the vertex's value.
    + Edge* adList: a singly linked list representing the adjacent edges that have this vertex as their starting vertex (from).
- Class Edge representing an edge in graph. It has some attributes: 
    + VertexNode* fromNode - VertexNode* toNode: represents the starting vertex (from) and ending vertex (to) of this edge.
    + float weight: edge's weight.
 
Requirements: In class VertexNode, implement methods getEdge, connectTo, addAdjacentEdge, and removeTo. 
Descriptions for each method are provided below. Ensure that all four methods are fully implemented before checking.

For example:

Test	
DGraph<int>::VertexNode* node0 = new DGraph<int>::VertexNode(0);
DGraph<int>::VertexNode* node1 = new DGraph<int>::VertexNode(1);
DGraph<int>::VertexNode* node2 = new DGraph<int>::VertexNode(2);
DGraph<int>::VertexNode* node3 = new DGraph<int>::VertexNode(3);

node0->connectTo(node1, 12.3);
node0->connectTo(node2, 13.3);
node0->connectTo(node3, 14);
node1->connectTo(node3, 176);

cout << node0->getEdge(node1)->toString() << endl;
cout << node1->getEdge(node3)->toString() << endl;

delete node0;
delete node1;
delete node2;
delete node3;

Result
E(0,1,12.3)
E(1,3,176)
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
 
     class Edge 
     {
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
typename DGraph<T>::Edge* DGraph<T>::VertexNode::getEdge(VertexNode* toNode) 
{
    //TODO: Iterate through the adjacency list of this vertex
    //      checking if there exists an edge with this vertex as the starting vertex 
    //      and "toNode" as the ending vertex. 
    //      If not return nullptr, else return that edge.
    Edge* curr = this->adList;
    while(curr)
    {
        if(curr->toNode == toNode) return curr;
        curr = curr->next;
    }
    return nullptr;
}

template<class T>
void DGraph<T>::VertexNode::addAdjacentEdge(Edge* newEdge) 
{
    //TODO: add newEdge to adjacency list of this vertex.
    newEdge->next = adList;
    adList = newEdge;
}

template<class T>
bool DGraph<T>::VertexNode::connectTo(VertexNode* toNode, float weight) 
{
    //TODO: get edge from this node to "toNode".
    
    //TODO: If the edge is not existed, create a new Edge and add it to the adjacency list. 
    //      If the edge is existed, update its weight.
    
    //TODO: Return true if a new Edge is created; otherwise, return false.
    Edge* edge = getEdge(toNode);
    if (edge == nullptr)
    {
        Edge* newEdge = new Edge(this, toNode, weight);
        addAdjacentEdge(newEdge);
        return true;
    }
    else
    {
        edge->weight = weight;
    }
    return false;
}

template<class T>
bool DGraph<T>::VertexNode::removeTo(VertexNode *toNode) 
{
    //TODO: remove the edge with "toNode" as the ending vertex from this node's adjacency list.
    
    //TODO: return true if success; otherwise, return false.
    Edge* curr = adList;
    Edge* prev = nullptr;
    while(curr != nullptr)
    {
        if(curr->toNode == toNode)
        {
            if(prev == nullptr)
            {
                adList = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}
