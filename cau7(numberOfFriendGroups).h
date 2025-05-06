/*
The relationship between a group of people is represented by an adjacency-list friends. 
If friends[u] contains v, u and v are friends.Friendship is a two-way relationship. 
Two people are in a friend group as long as there is some path of mutual friends connecting them.

Request: Implement function:

int numberOfFriendGroups(vector<vector<int>>& friends);
Where friends is the adjacency-list representing the friendship (this list has between 0 and 1000 lists). This function returns the number of friend groups.

Example:

Given a adjacency-list: [[1], [0, 2], [1], [4], [3], []]

There are 3 friend groups: [0, 1, 2], [3, 4], [5]

Note:

In this exercise, the libraries iostream, string, cstring, climits, utility, vector, list, stack, queue, map, 
unordered_map, set, unordered_set, functional, algorithm have been included and namespace std is used. You can write helper functions and class. 
Importing other libraries is allowed, but not encouraged.

For example:

Test	
vector<vector<int>> graph {
	{1},
	{0, 2},
	{1},
	{4},
	{3},
	{}
};
cout << numberOfFriendGroups(graph);
Result
3
*/

#include <bits/stdc++.h>
using namespace std;

//! ANSWER
#include <stack>

void dfs(int v, const vector<std::vector<int>>& friends, vector<bool>& visited) 
{
    // Đánh dấu đỉnh v là đã thăm
    visited[v] = true;
    
    // Duyệt qua tất cả bạn bè của v
    for (int neighbor : friends[v]) 
    {
        if (!visited[neighbor]) dfs(neighbor, friends, visited);
    }
}

int numberOfFriendGroups(vector<vector<int>>& friends) 
{
    int n = friends.size(); // Số người
    if (n == 0) return 0;   // Nếu không có người, trả về 0 nhóm
    
    // Mảng đánh dấu các đỉnh đã thăm
    vector<bool> visited(n, false);
    
    int groups = 0; // Đếm số nhóm bạn
    // Duyệt qua tất cả các đỉnh
    for (int v = 0; v < n; ++v) 
    {
        if (!visited[v]) 
        {
            // Nếu đỉnh chưa thăm, chạy DFS để thăm toàn bộ thành phần liên thông
            dfs(v, friends, visited);
            groups++; // Tăng số nhóm
        }
    }
    return groups;
}