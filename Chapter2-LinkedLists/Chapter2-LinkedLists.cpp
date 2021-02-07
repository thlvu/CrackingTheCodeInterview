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

struct Int
{
    int data;
};


struct PalindromeNode
{
    Node* node;
    bool ok;
};


Node* makeNode(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = nullptr;

    return node;
}

Node* makeList(vector<int> &vec)
{
    if (vec.size() == 0) {
        return nullptr;
    }
    Node* head = makeNode(0);    
    Node* tail = head;

    for (int i = 0; i < vec.size(); ++i)
    {
        Node* newTail = makeNode(vec[i]);

        tail->next = newTail;
        tail = tail->next;
    }

    return head->next;
}


void print(Node* head)
{
    printf("\n");
    while (head != nullptr)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}

Node* reverse(Node* head) 
{
    Node* rhead = (Node*)malloc(sizeof(Node));
    rhead = nullptr;

    Node* node = head;
    while (node != nullptr)
    {
        Node* nnode = node->next;
        node->next = rhead;
        rhead = node;
        node = nnode;
    }
    return rhead;
}

int size(Node* head)
{
    Node* node = head;
    int sz = 0;
    
    while (node != nullptr)
    {
        ++sz;
        node = node->next;
    }
    return sz;
}

Node* pad(Node* head, int pad, int data) {
    if (pad == 0)
    {
        return head;
    }

    Node* nhead = makeNode(data);
    Node* node = nhead;

    while (--pad > 0)
    {
        node->next = makeNode(data);
        node = node->next;
    }
    node->next = head;
    return nhead;
}

Node* stackPut(Node* head, int newData)
{
    Node* nhead = makeNode(newData);
    nhead->next = head;

    return nhead;
}

Node* stackPop(Node* head, Int* container)
{
    container->data = head->data;

    Node* nhead = head->next;
    free(head);

    return nhead;
}

bool stackEmpty(Node* head)
{
    return (size(head) == 0);
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

Node* sumListsReversed(Node* l1, Node* l2)
{
    Node* phead = (Node*)malloc(sizeof(Node));
    phead->data = 0;
    phead->next = nullptr;

    Node* tnode = phead;

    int up = 0;
    while (l1 != nullptr || l2 != nullptr)
    {
        int d;
        if (l1 == nullptr) d = l2->data;
        else if (l2 == nullptr) d = l1->data;
        else d = l1->data + l2->data;

        d += up;
        up = d / 10;
        d -= 10*up;

        Node* n = (Node*)malloc(sizeof(Node));
        n->data = d;
        tnode->next = n;
        tnode = n;

        if (l1 != nullptr) l1 = l1->next;
        if (l2 != nullptr) l2 = l2->next;
    }

    if (up > 0)
    {
        Node* n = (Node*)malloc(sizeof(Node));
        n->data = up;
        tnode->next = n;
        tnode = n;
    }

    tnode->next = nullptr;

    return phead->next;
}

Node* sumListsForward1(Node* l1, Node* l2)
{
    Node* l1Reversed = reverse(l1);
    Node* l2Reversed = reverse(l2);

    return reverse(sumListsReversed(l1Reversed, l2Reversed));
}

Node* sumListsForward2(Node* l1, Node* l2, int ridx)
{
    if (ridx == 0)
    {
        int data = l1->data + l2->data;
        return makeNode(data);
    }
    else
    {
        Node* tnode = sumListsForward2(l1->next, l2->next, ridx - 1);
        int carry = tnode->data / 10;
        tnode->data = tnode->data - 10*carry;

        int data = carry + l1->data + l2->data;
        Node* node = makeNode(data);

        node->next = tnode;

        return node;
    }
}

Node* sumListsForward2(Node* l1, Node* l2)
{
    int sz1 = size(l1);
    int sz2 = size(l2);
    int sz = max(sz1, sz2);

    if (sz1 > sz2)
    {
        l2 = pad(l2, sz1 - sz2, 0);
    }
    else if (sz1 < sz2)
    {
        l1 = pad(l1, sz2 - sz1, 0);
    }
    Node* head = sumListsForward2(l1, l2, sz - 1);
    
    if (head->data >= 10)
    {
        int carry = head->data / 10;
        head->data = head->data - 10*carry;

        Node* nhead = makeNode(carry);
        nhead->next = head;

        return nhead;
    }
    else
    {
        return head;
    }
}

// Using stack.
bool palindrome1(Node* head)
{
    int sz = size(head);
    int szHalf = sz / 2;

    Node* node = head;
    Node* stack = (Node*)malloc(sizeof(Node));
    stack = nullptr;

    for (int i = 0; i < szHalf; ++i)
    {
        stack = stackPut(stack, node->data);
        node = node->next;
    }

    if (sz % 2 == 1)
    {
        node = node->next;
    }
    
    Int* intContainer = (Int*)malloc(sizeof(Int));
    for (int i = 0; i < szHalf; ++i)
    {
        stack = stackPop(stack, intContainer);
        if (intContainer->data != node->data)
        {
            return false;
        }
        node = node->next;
    }
    return true;
}

PalindromeNode palindrome2(Node* head, Node* node, int sz, int idx)
{
    bool even = sz % 2 == 0;
    int mid = sz / 2;

    if (idx == mid - 1)
    {
        node = node->next;
        if (!even)
        {
            node = node->next;
        }
        PalindromeNode pn;
        pn.node = node;
        pn.ok = head->data == node->data;
        
        return pn;
    }
    else
    {
        PalindromeNode ppn = palindrome2(head->next, node->next, sz, idx + 1);
        if (!ppn.ok)
        {
            ppn.node = ppn.node->next;
            return ppn;
        }
        else
        {
            PalindromeNode pn;
            pn.node = ppn.node->next;
            pn.ok = pn.node->data == head->data;
            return pn;
        }
    }
}


bool palindrome2(Node* head)
{
    int sz = size(head);
    PalindromeNode pn = palindrome2(head, head, sz, 0);
    return pn.ok;
}


Node* intersection(Node* l1, Node* l2)
{
    unordered_map<Node*, bool> map;
    int sz1 = size(l1);
    int sz2 = size(l2);

    Node* shead;
    Node* lhead;

    if (sz1 > sz2)
    {
        shead = l2;
        lhead = l1;
    }
    else
    {
        shead = l1;
        lhead = l2;
    }
    while (shead != nullptr)
    {
        map[shead] = true;
        shead = shead->next;
    }
    while (lhead != nullptr)
    {
        if (map.find(lhead) != map.end())
        {
            return lhead;
        }
        lhead = lhead->next;
    }
    return nullptr;
}


Node* loopDetection(Node* head)
{
    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr)
    {
        if (fast->next == nullptr || fast->next->next == nullptr) { return nullptr; }

        slow = slow->next;
        fast = fast->next->next;

        if (fast == slow) { break; }
    }
    fast = head;
    while (fast != slow)
    {
        
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}


int main(void)
{
    int arr[16] = { 1, 1, 3, 3, 5, 3, 2, 2, 5, 5, 5, 5, -1, 2, 0, 3};
    vector<int> vec;
    for (int i = 0; i < 16; ++i)
    {
        int e = arr[i];
        vec.push_back(e);
    }
    Node* ll1 = makeList(vec);
    print(ll1);

    removeDups2(ll1);
    print(ll1);

    Node* ll1_2 = makeList(vec);
    print(ll1_2);

    removeDups2(ll1_2);
    print(ll1_2);

    Node* ll2 = makeList(vec);
    print(ll2);
    
    Node* ll2_k3 = returnKthToLast(ll2, 3);
    Node* ll2_k4 = returnKthToLast(ll2, 4);
    Node* ll2_k7 = returnKthToLast(ll2, 7);
    Node* ll2_k1 = returnKthToLast(ll2, 1);
    printf("\n(K: %d, data: %d)", 3, ll2_k3->data);
    printf("\n(K: %d, data: %d)", 4, ll2_k4->data);
    printf("\n(K: %d, data: %d)", 7, ll2_k7->data);
    printf("\n(K: %d, data: %d)", 1, ll2_k1->data);
    
    Node* ll3 = makeList(vec);
    print(ll3);

    deleteMiddleNode(ll3);
    print(ll3);

    Node* ll4 = makeList(vec);
    print(ll4);

    ll4 = partition(ll4, 3);
    print(ll4);

    int a1[6] = { 7, 7, 7, 9, 0, 5 };
    vector<int> v1;
    for (int i = 0; i < 6; ++i)
    {
        int e = a1[i];
        v1.push_back(e);
    }
    Node* l1 = makeList(v1);
    print(l1);

    int a2[6] = { 5, 5, 2, 3, 8, 9 };
    vector<int> v2;
    for (int i = 0; i < 6; ++i)
    {
        int e = a2[i];
        v2.push_back(e);
    }
    Node* l2 = makeList(v2);
    print(l2);

    Node* l1l2 = sumListsReversed(l1, l2);
    print(l1l2);

    Node* ll5 = makeList(vec);
    print(ll5);

    ll5 = reverse(ll5);
    print(ll5);

    l1 = makeList(v1);
    l2 = makeList(v2);

    print(l1);
    print(l2);

    l1l2 = sumListsForward1(l1, l2);
    print(l1l2);

    l1 = makeList(v1);
    l2 = makeList(v2);

    l1l2 = sumListsForward2(l1, l2);
    print(l1l2);

    int a3[6] = { 5, 1, 2, 2, 1, 5 };
    vector<int> v3;
    for (int i = 0; i < 6; ++i)
    {
        int e = a3[i];
        v3.push_back(e);
    }
    Node* l3 = makeList(v3);

    print(l3);
    printf("\n%s", palindrome1(l3) ? "true" : "false");

    l3 = makeList(v3);
    printf("\n%s", palindrome2(l3) ? "true" : "false");

    Node* h1 = makeNode(1);
    Node* h2 = makeNode(2);
    Node* h3 = makeNode(3);
    Node* h4 = makeNode(4);
    Node* h5 = makeNode(5);
    Node* h12 = makeNode(1);
    Node* h22 = makeNode(2);
    Node* h32 = makeNode(3);

    h1->next = h2;
    h2->next = h3;
    h3->next = h4;
    h4->next = h5;
    h12->next = h22;
    h22->next = h32;
    h32->next = h4;

    Node* inode = intersection(h1, h12);
    printf("\nIntersection: %d", inode->data);

    h1->next = h2;
    h2->next = h3;
    h3->next = h4;
    h4->next = h5;
    h5->next = h3;

    Node* cnode = loopDetection(h1);
    printf("\nCircular Node: %d", cnode->data);

    return 0;
}
