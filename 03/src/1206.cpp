#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

class MyStack
{
    private:
        Node *head;
        Node *top;

    public:
        MyStack();
        void onCreate();
        bool push(int data);
        int pop();
        int peek();
        bool isEmpty();
        ~MyStack();
};

MyStack::MyStack():
    head(NULL),
    top(NULL)
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
}

bool MyStack::push(int data)
{
    top = new Node;
    if(top == NULL)
        return false;
    top->data = data;
    top->next = head;
    head = top;
    return true;
}

int MyStack::pop()
{
    if(top == NULL)
        return -1;
    int data = top->data;
    head = top->next;
    delete top;
    top = head;
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

MyStack::~MyStack()
{
    while(head != NULL)
    {
        head = top->next;
        delete top;
        top = head;
    }
}

class PascalChecker
{
    private:
        bool compareChar(const char ch1[], const char ch2[], int size);
        char ch_begin[6], ch_end[4], ch_if[3], ch_then[5], ch_else[5];
        enum LeftPair
        {
            BEGIN,
            IF,
            THEN
        }   left_pair;
        MyStack pair_stack;

    public:
        PascalChecker();
        void onCreate();
        bool checkPair(char code[]);
};

bool PascalChecker::compareChar(const char ch1[], const char ch2[], int size)
{
    for(int i=0;i<size;i++)
    {
        if(ch1[i]==0||ch2[i]==0)
        {
            if(ch1[i]==0&&ch2[i]==0)
            {
                break;
            }
            else
            {
                return false;
            }
        }
        if(ch1[i]!=ch2[i])
            return false;
    }
    return true;
}

PascalChecker::PascalChecker()
{}

void PascalChecker::onCreate()
{
    pair_stack.onCreate();
    char tmp_begin[7] = "begin ",
         tmp_end[5] = "end ",
         tmp_if[4] = "if ",
         tmp_then[6] = "then ",
         tmp_else[6] = "else ";
    for(int i=0; i<6; ++i)
        ch_begin[i] = tmp_begin[i];
    for(int i=0; i<4; ++i)
        ch_end[i] = tmp_end[i];
    for(int i=0; i<3; ++i)
        ch_if[i] = tmp_if[i];
    for(int i=0; i<5; ++i)
        ch_then[i] = tmp_then[i];
    for(int i=0; i<5; ++i)
        ch_else[i] = tmp_else[i];
}

bool PascalChecker::checkPair(char code[])
{
    char *check_point;
    check_point = code;
    int last_pair = -1;
    /*
    while(*check_point != 0)
    {
        if(compareChar(check_point, ch_begin, 5))
        {
            pair_stack.push(BEGIN);
            ++check_point;
            break;
        }
        if(compareChar(check_point, ch_if, 2))
            return false;
        if(compareChar(check_point, ch_end, 3))
            return false;
        if(compareChar(check_point, ch_then, 4))
            return false;
        if(compareChar(check_point, ch_else, 4))
            return false;

        ++check_point;
    }*/
    while(*check_point != 0)
    {
        if(compareChar(check_point, ch_begin, 6))
            pair_stack.push(BEGIN);
        if(compareChar(check_point, ch_if, 3))
        {
            //if(pair_stack.isEmpty())
                //return false;
            pair_stack.push(IF);
        }
        if(compareChar(check_point, ch_end, 4))
        {
            do
            {
                last_pair = pair_stack.pop();
            }
            while(last_pair == THEN && !pair_stack.isEmpty());
            if(last_pair != BEGIN)
                return false;
            last_pair = -1;
        }
        if(compareChar(check_point, ch_then, 5))
        {
            if(pair_stack.pop() != IF)
                return false;
            else
                pair_stack.push(THEN);
        }
        if(compareChar(check_point, ch_else, 5))
        {
            if(pair_stack.pop() != THEN)
                return false;
        }
        ++check_point;
    }
    if(pair_stack.isEmpty())
        return true;
    else
        return false;
}

int main(void)
{
    PascalChecker pascal_check;
    pascal_check.onCreate();
    char code[4000]={0};
    for(int i=0; i<4000; ++i)
    {
        code[i] = cin.get();
        if(code[i] == 0 || code[i] == 10)
            code[i] = ' ';
        if(cin.eof())
        {
            code[i+1] = 0;
            break; 
        }
    }
    if(pascal_check.checkPair(code))
        cout << "Match!" << endl;
    else
        cout << "Error!" << endl;
    return 0;
}
