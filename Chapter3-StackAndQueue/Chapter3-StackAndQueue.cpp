#include <iostream>
#include <vector>

using namespace std;


class Stack3in1 {
private:
    int arr[300];
    int s1 = 0 - 1;
    int s2 = 100 - 1;
    int s3 = 200 - 1;

    void pop(int i)
    {
        if (i == 0 && s1 >= 0) --s1;
        if (i == 1 && s2 >= 100) --s2;
        if (i == 2 && s3 >= 200) --s3;
    }

    void push(int i, int k)
    {
        if (i == 0 && s1 < 99) arr[++s1] = k;
        if (i == 1 && s2 < 199) arr[++s2] = k;
        if (i == 2 && s3 < 299) arr[++s3] = k;
    }

    int peak(int i)
    {
        if (i == 0 & s1 >= 0) return arr[s1];
        if (i == 1 & s2 >= 100) return arr[s2];
        if (i == 2 & s3 >= 200) return arr[s3];
        return -1;
    }

    bool isEmpty(int i)
    {
        if (i == 0 && s1 == -1) return true;
        if (i == 1 && s1 == 99) return true;
        if (i == 2 && s1 == 199) return true;
        return false;
    }
};

/* Three in one - Solution in the book

Approach 1: Fixed divisision
    - Same to my solution.

Approach 2: Flexible division
    - Too complex to implement in an interview.
    - It is important to focus on writing clean and maintainable.
*/


struct Node {
    int data;
    int min;
    Node* next;
};

class StackMin {
private:
    Node* head = nullptr;

public:
    void pop()
    {
        Node* nhead = head->next;
        free(head);
        head = nhead;
    }

    void push(int data)
    {
        Node* nhead = (Node*)malloc(sizeof(Node));
        nhead->data = data;
        nhead->next = head;
        
        if (head == nullptr) nhead->min = data;
        else nhead->min = data < head->min ? data : head->min;

        head = nhead;
    }

    int peak()
    {
        return head->data;
    }

    bool empty()
    {
        return head == nullptr;
    }

    int min()
    {
        return head->min;
    }
};

/* Stack Min - The solution in the book.

- First approach is same to my implementation.
- However this needed min value space for every node and this is not memory efficient.

- Better option is using additional stack that keeps mininum nodes.

*/


class StackOfPlateStack {
private:
    int arr[10];
    int current = -1;

public:
    void push(int data)
    {
        arr[++current] = data;
    }

    int peak()
    {
        if (current >= 0) return arr[current];
        else return INT32_MIN;
    }

    void pop()
    {
        if (current >= 0) --current;
    }

    bool empty()
    {
        if (current == -1) return true;
        else return false;
    }
    
    bool full()
    {
        if (current == 9) return true;
        else return false;
    }
};


struct SNode {
    StackOfPlateStack* stack;
    SNode* next;
};

class SList
{
public:
    SNode* head = nullptr;
    int size = 0;

    SNode* get(int idx)
    {
        SNode* node = head;
        for (int i = 0; i < size - idx - 1; ++i) node = node->next;
        
        return node;
    }

    SNode* get()
    {
        return head;
    }

    void add()
    {
        SNode* node = (SNode*) malloc(sizeof(SNode));
        node->stack = new StackOfPlateStack();
        node->next = head;
        head = node;
        ++size;
    }

    void remove()
    {
        head = head->next;
        --size;
    }
};

class StackOfPlate{
public:
    SList slist = SList();
    void push(int data)
    {
        SNode* h = slist.get();
        if (h == nullptr || h->stack->full()) slist.add();

        StackOfPlateStack* hs = slist.get()->stack;
        hs->push(data);
    }

    int peak()
    {
        return slist.get()->stack->peak();
    }

    void pop()
    {
        slist.get()->stack->pop();
        if (slist.get()->stack->empty()) slist.remove();
    }

    void popAt(int idx)
    {
        slist.get(idx)->stack->pop();
    }

    bool empty()
    {
        return slist.get() == nullptr || slist.get()->stack->empty();
    }
};

/* Stack Of Plates - Solution in the book.
    - Same to my implementaion.
    - In the case of PopAt, solution shifts left overs so that stacks are full except the last.
    - But this is a choice in some sense so it would be more imporatnt 
        to explain interviewer why implement like that.
*/


class Stack{
public:
    Node* head = nullptr;
    void push(int data)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = data;
        node->next = head;
        head = node;
    }

    void pop()
    {
        head = head->next;
    }

    int peak()
    {
        return head->data;
    }

    bool empty()
    {
        return head == nullptr;
    }
};


class Queue{
private:
    Stack s1 = Stack();
    Stack s2 = Stack();

public:
    void push(int data)
    {
        s1.push(data);
    }

    int peak()
    {
        while (!s1.empty())
        {
            s2.push(s1.peak());
            s1.pop();
        }
        int data = s2.peak();

        while (!s2.empty())
        {
            s1.push(s2.peak());
            s2.pop();
        }

        return data;
    }

    void pop()
    {
        while (!s1.empty())
        {
            s2.push(s1.peak());
            s1.pop();
        }
        s2.pop();

        while (!s2.empty())
        {
            s1.push(s2.peak());
            s2.pop();
        }
    }

    bool empty()
    {
        return s1.empty();
    }
};

/* Queue via stacks - Solution in the book.
    - Solution suggests lazy movement.
    - e.g, let 3 -> 2 -> 1 -> 4 -> 5
    - if peak after push 1, move values to other stack. It looks like 1 -> 2 -> 3
    - 3 is peaked. 
    - Then suppose pop two items. It has one item so that do nothing.
    - If pop three items, it is empty. Then move values again. It looks like 5 -> 4.
    - Then peak or pop again.
*/

int main(void)
{
    StackMin stackMin = StackMin();
    stackMin.push(2);
    printf("Min: %d\n", stackMin.min());
    stackMin.push(3);
    printf("Min: %d\n", stackMin.min());
    stackMin.push(1);
    printf("Min: %d\n", stackMin.min());
    stackMin.pop();
    printf("Min: %d\n", stackMin.min());
    stackMin.pop();
    printf("Min: %d\n", stackMin.min());

    StackOfPlate sop = StackOfPlate();
    for (int i = 0; i < 100; ++i)
    {
        sop.push(i);
        printf("%d ", i);
    }
    printf("\n");

    while (!sop.empty())
    {
        printf("%d ", sop.peak());
        sop.pop();
    }
    printf("\n");

    Queue q = Queue();
    for (int i = 0; i < 20; ++i)
    {
        q.push(i);
        printf("%d ", i);
    }
    printf("\n");

    while (!q.empty())
    {
        printf("%d ", q.peak());
        q.pop();
    }
    printf("\n");

    return 0;
}