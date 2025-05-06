/*
Implement Depth-first search

Adjacency *DFS(int v);
where Adjacency is a structure to store list of number.
For example:

Test	
int V = 8, visited = 0;

Graph g(V);
Adjacency *arr;
int edge[][2] = {{0,1}, {0,2}, {0,3}, {0,4}, {1,2}, {2,5}, {2,6}, {4,6}, {6,7}};
for(int i = 0; i < 9; i++)
{
	g.addEdge(edge[i][0], edge[i][1]);
}

// g.printGraph();
// cout << endl;
arr = g.DFS(visited);
arr->printArray();
delete arr;
Result
0 1 2 5 6 4 7 3
*/

#include <bits/stdc++.h>
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

class Graph
{
private:
	int V;
	Adjacency *adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
	}
	
	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}
	
    void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
	
	//! ANSWER
	// Helper function
	void DFSUtil(int v, bool visited[], Adjacency* result)
	{
	    // Đánh dấu đỉnh v là đã thăm và thêm vào kết quả
        visited[v] = true;
        result->push(v);
        
        // Duyệt qua tất cả các đỉnh kề của v
        for (int i = 0; i < adj[v].getSize(); i++) 
        {
            int neighbor = adj[v].getElement(i);
            // Nếu đỉnh kề chưa được thăm
            if (!visited[neighbor]) DFSUtil(neighbor, visited, result);
        }
	}
	
	Adjacency *DFS(int v)
    {
        // v is a vertex we start DFS
        // Tạo một đối tượng Adjacency để lưu kết quả
        Adjacency* result = new Adjacency();
        
        // Mảng đánh dấu các đỉnh đã thăm
        bool* visited = new bool[V]();
        
        // Gọi hàm DFS đệ quy
        DFSUtil(v, visited, result);
        
        // Giải phóng bộ nhớ mảng visited
        delete[] visited;
        
        // Trả về danh sách kết quả
        return result;
	}
};