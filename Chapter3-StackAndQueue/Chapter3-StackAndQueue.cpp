#include <iostream>

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

    return 0;
}