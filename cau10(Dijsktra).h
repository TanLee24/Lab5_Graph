/*
Given a graph and a source vertex in the graph, find shortest paths from source to destination vertice in the given graph using Dijsktra's algorithm.

Following libraries are included: iostream, vector, algorithm, climits, queue

Note: All testcases have a fixed number of vertices set to 6.

For example:

Test	
int n = 6;
int init[6][6] = {
	{0, 10, 20, 0, 0, 0},
	{10, 0, 0, 50, 10, 0},
	{20, 0, 0, 20, 33, 0},
	{0, 50, 20, 0, 20, 2},
	{0, 10, 33, 20, 0, 1},
	{0, 0, 0, 2, 1, 0} };

int** graph = new int*[n];
for (int i = 0; i < n; ++i) {
	graph[i] = init[i];
}

cout << Dijkstra(graph, 0, 1);
Result
10
*/

#include <bits/stdc++.h>
using namespace std;
//! ANSWER
int Dijkstra(int** graph, int src, int dst) 
{
    const int V = 6; // Số đỉnh cố định
    vector<int> dist(V, INT_MAX); // Khoảng cách ngắn nhất từ src đến mỗi đỉnh
    vector<bool> visited(V, false); // Đánh dấu các đỉnh đã xử lý
    
    // Hàng đợi ưu tiên để chọn đ� acceleration với khoảng cách nhỏ nhất
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Khởi tạo khoảng cách từ src đến chính nó là 0
    dist[src] = 0;
    pq.push({0, src}); // {khoảng cách, đỉnh}
    
    while (!pq.empty()) 
    {
        // Lấy đỉnh có khoảng cách nhỏ nhất
        int u = pq.top().second;
        pq.pop();
        
        // Nếu đỉnh đã được xử lý, bỏ qua
        if (visited[u]) continue;
        
        // Đánh dấu đỉnh u là đã xử lý
        visited[u] = true;
        
        // Duyệt qua tất cả các đỉnh kề của u
        for (int v = 0; v < V; ++v) 
        {
            // Nếu có cạnh từ u đến v (graph[u][v] != 0) và v chưa được xử lý
            if (!visited[v] && graph[u][v] != 0) 
            {
                // Cập nhật khoảng cách đến v nếu tìm thấy đường đi ngắn hơn qua u
                if (dist[u] + graph[u][v] < dist[v]) 
                {
                    dist[v] = dist[u] + graph[u][v];
                    pq.push({dist[v], v});
                }
            }
        }
    }
    // Trả về khoảng cách đến dst, hoặc INT_MAX nếu không có đường đi
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}