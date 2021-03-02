#include <iostream>
#include <vector>
#include <queue>

using namespace std;


struct GraphNode {
    int data;
    int visited;
    vector<GraphNode> adjacents;
};

struct Graph {
    vector<GraphNode> nodes;
};

bool routeBetweenNodes(GraphNode node1, GraphNode node2)
{
    queue<GraphNode> q1;
    queue<GraphNode> q2;

    q1.push(node1);
    q2.push(node2);

    while (true)
    {
        if (q1.empty()) { return false; }

        GraphNode n = q1.front();
        q1.pop();

        if (n.visited == 2) { return true; }
        else { n.visited = 1; }

        for (int i = 0; i < n.adjacents.size(); ++i)
        {
            if (n.adjacents[i].visited != 1) { q1.push(n.adjacents[i]); }
        }

        if (q2.empty()) { return false; }

        n = q2.front();
        q1.pop();

        if (n.visited == 1) { return true; }
        else { n.visited = 2; }

        for (int i = 0; i < n.adjacents.size(); ++i)
        {
            if (n.adjacents[i].visited != 2) { q2.push(n.adjacents[i]); }
        }
    }
    return true;
}

/* Route between nodes - Solution in the book.
*
* Solution suggets just traverse from one start node, not for both sides.
* The reason, I thought, is that it is just a simple question to check interviewee knows DFS and BFS.
* But as book introduced, run bfs for both sides are more effective if implementing BFS.
* BFS family advantages over DFS in efficiency and shortest path recognition, 
* except that DFS is more easy to implement.
*/

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* minimalTree(vector<int> & arr, int start, int end)
{
    if (start > end) { return nullptr; }

    int mid = (start + end) / 2;
    TreeNode* root = (TreeNode*) malloc(sizeof(TreeNode));

    root->data = arr[mid];
    root->left = minimalTree(arr, start, mid-1);
    root->right = minimalTree(arr, mid+1, end);

    return root;
}

void inorderTraverse(TreeNode* root, int i)
{
    if (root != nullptr) 
    { 
        inorderTraverse(root->left, i+1); 
        printf("%d(%d) ", root->data, i);
        inorderTraverse(root->right, i+1);
    }
}

/* Minimal Tree - Solution in the book
*
* Suggested solution in the book is same to my implementation.
* But one thing I regret is that it does not construct complete binary tree.
*/

int main(void)
{
    vector<int> arr;
    for (int i = 0; i < 15; ++i) { arr.push_back(i); }
    
    TreeNode* root = minimalTree(arr, 0, 14);
    inorderTraverse(root, 0);

    return 0;
}