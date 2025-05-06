/*
Implement topologicalSort function on a graph. (Ref here)

void topologicalSort();
where Adjacency is a structure to store list of number. Note that, the vertex index starts from 0. 
To match the given answer, please always traverse from 0 when performing the sorting.
For example:

Test	
Graph g(6);
g.addEdge(5, 2);
g.addEdge(5, 0);
g.addEdge(4, 0);
g.addEdge(4, 1);
g.addEdge(2, 3);
g.addEdge(3, 1);

g.topologicalSort();
Result
5 4 2 3 1 0
*/

#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const &i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const &i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx) 
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph {

    int V;
    Adjacency* adj;

public:
    Graph(int V){
        this->V = V;
        adj = new Adjacency[V];
    }
    void addEdge(int v, int w){
        adj[v].push(w);
    }
    
    //! ANSWER
    // Hàm DFS hỗ trợ để thực hiện topological sort
    void dfsUtil(int v, vector<bool>& visited, stack<int>& result) 
    {
        // Đánh dấu đỉnh v là đã thăm
        visited[v] = true;
        
        // Duyệt qua tất cả các đỉnh kề của v
        for (int i = 0; i < adj[v].getSize(); i++) 
        {
            int neighbor = adj[v].getElement(i);
            if (!visited[neighbor]) 
            {
                dfsUtil(neighbor, visited, result);
            }
        }
        
        // Thêm đỉnh v vào ngăn xếp sau khi duyệt hết các đỉnh kề
        result.push(v);
    }
    
    void topologicalSort()
    {
        //TODO
        // Mảng đánh dấu các đỉnh đã thăm
        vector<bool> visited(V, false);
        // Ngăn xếp lưu trữ thứ tự topological
        stack<int> result;
        
        // Duyệt qua tất cả các đỉnh, bắt đầu từ 0
        for (int v = 0; v < V; v++) 
        {
            if (!visited[v]) 
            {
                dfsUtil(v, visited, result);
            }
        }
        
        // In ra thứ tự topological từ ngăn xếp
        while (!result.empty()) 
        {
            cout << result.top() << " ";
            result.pop();
        }
    }
};