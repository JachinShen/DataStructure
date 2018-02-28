#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class MyStack {
private:
    Node* head;
    Node* top;
    int length;

public:
    MyStack();
    void onCreate();
    bool push(int data);
    int pop();
    int peek();
    bool isEmpty();
    int getLength();
    ~MyStack();
};

MyStack::MyStack()
    : head(NULL)
    , top(NULL)
    , length(0)
{
}

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

bool MyStack::push(int data)
{
    top = new Node;
    if (top == NULL)
        return false;
    top->data = data;
    top->next = head;
    head = top;
    ++length;
    return true;
}

int MyStack::pop()
{
    if (top == NULL)
        return -1;
    int data = top->data;
    head = top->next;
    delete top;
    top = head;
    --length;
    return data;
}

int MyStack::peek()
{
    if (top == NULL)
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
    while (head != NULL) {
        head = top->next;
        delete top;
        top = head;
    }
}

class MyQueue {
private:
    int* data;
    int front, end, max_size;

public:
    MyQueue();
    MyQueue(int size);
    int touch();
    int pick();
    bool append(int data_add);
    bool isEmpty();
    ~MyQueue();
};

MyQueue::MyQueue()
    : data(NULL)
    , front(0)
    , end(-1)
    , max_size(0)
{
}

MyQueue::MyQueue(int size)
    : front(0)
    , end(-1)
    , max_size(size)
{
    data = new int[size];
}

int MyQueue::touch()
{
    if (front <= end)
        return data[front];
    else
        return -1;
}

int MyQueue::pick()
{
    if (front <= end)
        return data[front++];
    else
        return -1;
}

bool MyQueue::append(int data_add)
{
    ++end;
    if (end < max_size) {
        data[end] = data_add;
        return true;
    } else
        return false;
}

bool MyQueue::isEmpty()
{
    return front > end;
}

MyQueue::~MyQueue()
{
    if (data != NULL)
        delete[] data;
}

class Arrange {
private:
    int N, M;
    MyStack station_stack;
    MyQueue wanted_arrange;
    bool checkOnce(int in_train);
    void cleanPair();

public:
    Arrange();
    void onCreate();
    void getNM();
    void check();
};

Arrange::Arrange()
    : wanted_arrange(1000)
{
}

void Arrange::onCreate()
{
    station_stack.onCreate();
}

void Arrange::getNM()
{
    cin >> N;
    cin >> M;
    int data = 0;
    for (int i = 0; i < N; ++i) {
        cin >> data;
        wanted_arrange.append(data);
    }
}

void Arrange::check()
{
    for (int i = 0; i < N; ++i) {
        if (!checkOnce(i)) {
            cout << "NO" << endl;
            return;
        }
    }
    cleanPair();
    if (wanted_arrange.isEmpty()
        && station_stack.isEmpty())
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

bool Arrange::checkOnce(int in_train)
{
    cleanPair();
    if (in_train == wanted_arrange.touch()) {
        wanted_arrange.pick();
        return true;
    }
    if (station_stack.getLength() < M) {
        station_stack.push(in_train);
        return true;
    } else
        return false;
}

void Arrange::cleanPair()
{
    while (!wanted_arrange.isEmpty()
        && !station_stack.isEmpty()
        && wanted_arrange.touch() == station_stack.peek()) {
        wanted_arrange.pick();
        station_stack.pop();
    }
}

int main(void)
{
    /*
    int tmp;
    MyQueue test(10);
    for(int i=0; i<5; ++i)
    {
        cin >> tmp;
        test.append(tmp);
    }
    cout << test.touch()<<endl;
    cout << test.touch()<<endl;
    cout << test.pick()<<endl;
    cout << test.pick()<<endl;
    */
    int count = 0;
    cin >> count;
    Arrange* arrange;
    arrange = new Arrange[count];
    for (int i = 0; i < count; ++i) {
        arrange[i].getNM();
    }
    for (int i = 0; i < count; ++i)
        arrange[i].check();
    return 0;
}
