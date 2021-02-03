#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node* next = nullptr;
};


Node* makeLL(vector<int> &vec)
{
    if (vec.size() == 0) {
        return nullptr;
    }
    Node* head = (Node*) malloc(sizeof(Node));
    head->data = 0;
    
    Node* tail = head;

    for (int i = 0; i < vec.size(); ++i)
    {
        int e = vec[i];
        Node* newTail = (Node*) malloc(sizeof(Node));
        newTail->data = e;
        newTail->next = nullptr;

        tail->next = newTail;
        tail = tail->next;
    }
    return head->next;
}


void printLL(Node* head)
{
    printf("\n");
    while (head != nullptr)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}

// removeDuplicates with buffer
void removeDups1(Node *head)
{
    if (head == nullptr)
    {
        return;
    }
    Node* slow = head;
    Node* fast = head->next;
    unordered_map<int, bool> buffer;

    while (fast != nullptr)
    {
        buffer[slow->data] = true;
        
        if (buffer.find(fast->data) != buffer.end())
        {
            slow->next = fast->next;
            free(fast);
            fast = slow->next;
        }
        else
        {
            slow = fast;
            fast = fast->next;
        }
    }
}

// removeDuplicates without buffer
void removeDups2(Node *head)
{
    Node* base = head;
    while (base != nullptr)
    {
        Node* slow = base;
        Node* fast = slow->next;
        while (fast != nullptr)
        {
            if (base->data == fast->data)
            {
                slow->next = fast->next;
                free(fast);
                fast = slow->next;
            }
            else
            {
                slow = fast;
                fast = fast->next;
            }
        }
        base = base->next;
    }
}


/* RemoveDups's solution in the book is same with me in both cases. */


Node* returnKthToLast(Node* head, int k)
{
    Node* node = head;
    for (int i = 0; i < k-1; ++i)
    {
        if (node == nullptr)
        {
            throw out_of_range("out of range");
        }
        node = node->next;
    }

    while (node->next != nullptr)
    {
        head = head->next;
        node = node->next;
    }
    return head;
}

/* Return Kth to Last' solution in the book.
* Firstly, clarify K start with 0 or 1.
* Two solutions are introduced.
* It says recursive solution is more intuitive but less optimal.
* But I felt hard to understand the recursive way.


* 1. Recursive solution.
* counting from back to front. If encounter kth element, anchoring to this element.

* === python code ===
    class Index:
        value = 0;

    def kth2last(li, k, i):
        if i >= len(li):
            return None
        
        at = kth2last(li, k, i + 1)
        Index.value += 1
        
        print(at, li, k, Index.value)
        
        if (Index.value == k):
            print("in")
            return li[i]
        else:
            print("out")
            return at

    li = [1,2,3,4,5,6,7]
    print(kth2last(li, 3, 0))

* === result ===
    None [1, 2, 3, 4, 5, 6, 7] 3 1                                                                                              
    out                                                                                                                         
    None [1, 2, 3, 4, 5, 6, 7] 3 2                                                                                              
    out                                                                                                                         
    None [1, 2, 3, 4, 5, 6, 7] 3 3                                                                                              
    in                                                                                                                          
    5 [1, 2, 3, 4, 5, 6, 7] 3 4                                                                                                 
    out                                                                                                                         
    5 [1, 2, 3, 4, 5, 6, 7] 3 5                                                                                                 
    out                                                                                                                         
    5 [1, 2, 3, 4, 5, 6, 7] 3 6                                                                                                 
    out                                                                                                                         
    5 [1, 2, 3, 4, 5, 6, 7] 3 7                                                                                                 
    out                                                                                                                         
    5


* 2. Iterative Solution.
This is same to my implementation.
*/


void deleteMiddleNode(Node* head)
{
    if (head == nullptr) return;
    if (head->next == nullptr) return;
    if (head->next->next == nullptr) return;

    Node* tNode = head;
    int sz = 0;
    while (tNode != nullptr)
    {
        tNode = tNode->next;
        sz++;
    }

    tNode = head;
    sz = sz / 2;
    
    for (int i = 0; i < sz; ++i)
    {
        tNode = tNode->next;
    }
    Node* delNode = tNode->next;
    tNode->next = tNode->next->next;
    free(delNode);
}

int partition(Node* head, int x, int np)
{
    if (head == nullptr) return np;
    if (head->next == nullptr) return np;
    if (head->next->next == nullptr) return np;

    Node* n1 = head->next;
    Node* n2 = head->next->next;

    if (n1->data >= x && n2->data < x)
    {
        n1->next = n2->next;
        n2->next = n1;
        head->next = n2;
        np++;
    }
    return partition(head->next, x, np);
}


/* Delete Middle Node Solution.
* The solution assumed that node that will be deleted is given, not the head.
* Delete this node is impossible because we have no access to the previous node.
* So solution suggest copy data and next from next node of a given node.
* By doing this, node is survived, but accessing node works loooks like that node deleted.
*/


Node* partition(Node* head, int x)
{
    Node* pHead = (Node*) malloc(sizeof(Node));
    pHead->data = 0;
    pHead->next = head;

    int c = 1;
    while (c != 0)
    {
        c = partition(pHead, x, 0);
    }

    return pHead->next;
}

/* Partition's solution
* First solution suggests make front linked list and rear linked list.
* Then, concatenate it.
* Second solution is similar, but make front linked list in reversed order,
* ===
    Node head = node;
    ...
    if (node.data < x)
    {
        node.next = head;
        head = node;
    }
    ...
* ===
* By doing so, we can remove local variables to track first node and last node of each list.    
*/

int main(void)
{
    int arr[16] = { 1, 1, 3, 3, 5, 3, 2, 2, 5, 5, 5, 5, -1, 2, 0, 3};
    vector<int> vec;
    for (int i = 0; i < 16; ++i)
    {
        int e = arr[i];
        vec.push_back(e);
    }
    Node* ll1 = makeLL(vec);
    printLL(ll1);

    removeDups2(ll1);
    printLL(ll1);

    Node* ll1_2 = makeLL(vec);
    printLL(ll1_2);

    removeDups2(ll1_2);
    printLL(ll1_2);

    Node* ll2 = makeLL(vec);
    printLL(ll2);
    
    Node* ll2_k3 = returnKthToLast(ll2, 3);
    Node* ll2_k4 = returnKthToLast(ll2, 4);
    Node* ll2_k7 = returnKthToLast(ll2, 7);
    Node* ll2_k1 = returnKthToLast(ll2, 1);
    printf("\n(K: %d, data: %d)", 3, ll2_k3->data);
    printf("\n(K: %d, data: %d)", 4, ll2_k4->data);
    printf("\n(K: %d, data: %d)", 7, ll2_k7->data);
    printf("\n(K: %d, data: %d)", 1, ll2_k1->data);
    
    Node* ll3 = makeLL(vec);
    printLL(ll3);

    deleteMiddleNode(ll3);
    printLL(ll3);

    Node* ll4 = makeLL(vec);
    printLL(ll4);

    ll4 = partition(ll4, 3);
    printLL(ll4);

    return 0;
}
