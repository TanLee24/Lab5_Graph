/*
Implement Breadth-first search

Adjacency *BFS(int v);
where Adjacency is a structure to store list of number. 
For example:

Test	
int V = 6;
int visited = 0;

Graph g(V);
Adjacency* arr = new Adjacency(V);
int edge[][2] = {{0,1},{0,2},{1,3},{1,4},{2,4},{3,4},{3,5},{4,5}};
    
for(int i = 0; i < 8; i++)
{
    g.addEdge(edge[i][0], edge[i][1]);
}
    
arr = g.BFS(visited);
arr->printArray();
delete arr;
Result
0 1 2 3 4 5

Test
int V = 6;
int visited = 2;

Graph g(V);
Adjacency* arr = new Adjacency(V);
int edge[][2] = {{0,1},{0,2},{1,3},{1,4},{2,4},{3,4},{3,5},{4,5}};
    
for(int i = 0; i < 8; i++)
{
    g.addEdge(edge[i][0], edge[i][1]);
}
    
arr = g.BFS(visited);
arr->printArray();
delete arr;
Result
2 0 4 1 3 5 
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

#include <queue>
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
	Adjacency *BFS(int v)
    {
        // v is a vertex we start BFS
        // Tạo một đối tượng Adjacency để lưu kết quả
        Adjacency* result = new Adjacency();
        
        // Mảng đánh dấu các đỉnh đã thăm
        bool* visited = new bool[V]();
        
        // Hàng đợi cho BFS
        std::queue<int> queue;
        
        // Đánh dấu đỉnh bắt đầu là đã thăm và thêm vào hàng đợi
        visited[v] = true;
        queue.push(v);
        result->push(v);
        
        // Duyệt BFS
        while (!queue.empty()) 
        {
            // Lấy đỉnh đầu tiên từ hàng đợi
            int current = queue.front();
            queue.pop();
            
            // Duyệt qua tất cả các đỉnh kề của current
            for (int i = 0; i < adj[current].getSize(); i++) 
            {
                int neighbor = adj[current].getElement(i);
                // Nếu đỉnh kề chưa được thăm
                if (!visited[neighbor]) 
                {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                    result->push(neighbor);
                }
            }
        }
        
        // Giải phóng bộ nhớ mảng visited
        delete[] visited;
        
        // Trả về danh sách kết quả
        return result;
	}
};