/*
Implement function to detect a cyclic in Graph

bool isCyclic();
Graph structure is defined in the initial code.


For example:

Test	
DirectedGraph g(8); 
int edege[][2] = {{0,6}, {1,2}, {1,4}, {1,6}, {3,0}, {3,4}, {5,1}, {7,0}, {7,1}};

for(int i = 0; i < 9; i++)
	g.addEdge(edege[i][0], edege[i][1]);

if(g.isCyclic()) 
	cout << "Graph contains cycle"; 
else
	cout << "Graph doesn't contain cycle";
Result
Graph doesn't contain cycle
*/

#include <iostream>
#include <vector>
#include <list>
using namespace std;

class DirectedGraph 
{ 
	int V;
	vector<list<int>> adj;
public:
	DirectedGraph(int V)
	{
		this->V = V; 
		adj = vector<list<int>>(V, list<int>());
	}
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}
	
    //! ANSWER
	// Hàm DFS hỗ trợ để kiểm tra chu trình
    bool dfsUtil(int v, vector<bool>& visited, vector<bool>& recStack) 
    {
        // Đánh dấu đỉnh v là đã thăm và thêm vào ngăn xếp đệ quy
        visited[v] = true;
        recStack[v] = true;
        
        // Duyệt qua tất cả các đỉnh kề của v
        for (int neighbor : adj[v]) 
        {
            // Nếu đỉnh kề chưa được thăm, chạy DFS cho nó
            if (!visited[neighbor]) {
                if (dfsUtil(neighbor, visited, recStack)) 
                {
                    return true; // Tìm thấy chu trình
                }
            }
            // Nếu đỉnh kề đã trong ngăn xếp đệ quy, có chu trình
            else if (recStack[neighbor]) 
            {
                return true;
            }
        }
        
        // Loại bỏ đỉnh v khỏi ngăn xếp đệ quy khi hoàn thành
        recStack[v] = false;
        return false; // Không tìm thấy chu trình
    }
	
	bool isCyclic()
	{
	    // Student answer
	    // Mảng đánh dấu các đỉnh đã thăm
        vector<bool> visited(V, false);
        // Mảng đánh dấu các đỉnh trong ngăn xếp đệ quy
        vector<bool> recStack(V, false);
        
        // Duyệt qua tất cả các đỉnh để xử lý trường hợp đồ thị không liên thông
        for (int v = 0; v < V; ++v) 
        {
            if (!visited[v]) 
            {
                // Gọi DFS cho đỉnh chưa thăm
                if (dfsUtil(v, visited, recStack)) 
                {
                    return true; // Tìm thấy chu trình
                }
            }
        }
        return false; // Không tìm thấy chu trình
	}
}; 