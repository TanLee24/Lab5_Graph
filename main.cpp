#include "cau10(Dijsktra).h"
using namespace std;

int main()
{
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

    return 0;
}