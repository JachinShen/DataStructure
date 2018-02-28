#include <iostream>
using namespace std;

struct Node
{
    unsigned long data;
    Node *next;
};

class MyStack
{
    private:
        Node *head;
        Node *top;
        int length;

    public:
        MyStack();
        void onCreate();
        bool push(unsigned long data);
        unsigned long pop();
        int peek();
        bool isEmpty();
        int getLength();
        ~MyStack();
};

MyStack::MyStack():
    head(NULL),
    top(NULL),
    length(0)
{}

void MyStack::onCreate()
{
    /*
    head = new Node;
    if(head == NULL)
        return false;
    top = head;
    head->next = NULL;
    return true;
    */
    head = NULL;
    top = NULL;
    length = 0;
}

bool MyStack::push(unsigned long data)
{
    top = new Node;
    if(top == NULL)
        return false;
    top->data = data;
    top->next = head;
    head = top;
    ++length;
    return true;
}

unsigned long MyStack::pop()
{
    if(top == NULL)
        return -1;
    unsigned long data = top->data;
    head = top->next;
    delete top;
    top = head;
    --length;
    return data;
}

int MyStack::peek()
{
    if(top == NULL)
        return -1;
    return top->data;
}

bool MyStack::isEmpty()
{
    return top == NULL;
}

int MyStack::getLength()
{
    return length;
}

MyStack::~MyStack()
{
    while(head != NULL)
    {
        head = top->next;
        delete top;
        top = head;
    }
}

unsigned long Ackerman2(unsigned long m, unsigned long n)
{
    if(m == 0)
        return n + 1;
    if(m > 0 && n == 0)
        return Ackerman2(m - 1, 1);
    return Ackerman2(m - 1, Ackerman2(m, n-1));
}

unsigned long Ackerman(unsigned long m, unsigned long n)
{
    MyStack task_stack;
    task_stack.push(m);
    task_stack.push(n);
    unsigned long tmp1, tmp2;
    while(1)
    {
        tmp2 = task_stack.pop();
        if(task_stack.isEmpty())
        {
            return tmp2;
        }
        tmp1 = task_stack.pop();
        if(tmp1 == 0)
        {
            task_stack.push(tmp2 + 1);
            continue;
        }
        if(tmp1 > 0 && tmp2 == 0)
        {
            task_stack.push(tmp1 - 1);
            task_stack.push(1);
            continue;
        }
        task_stack.push(tmp1 - 1);
        task_stack.push(tmp1);
        task_stack.push(tmp2 - 1);
    }
}

int main(void)
{
    unsigned long m, n;
    cin >> m >> n;
    //cout << Ackerman2(m, n) << endl;
    cout << Ackerman(m, n) << endl;
    return 0;
}
