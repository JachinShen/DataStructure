#include <iostream>
#define MAX_DATA_SIZE 65536+1
#define MAX_LOC_SIZE 30000+1
using namespace std;

template<class T>
class MyQueue
{
    private:
        struct QueueNode
        {
            T data;
            QueueNode *next = NULL;
        };

        QueueNode *head, *end, *tmp;
    public:
        MyQueue():head(NULL),end(NULL){}
        ~MyQueue()
        {
            while(!isEmpty())
                pick();
            delete head;
            delete end;
        }

        void create()
        {
            head = new QueueNode;
            end = new QueueNode;
            head->next = end;
        }

        void push(T data)
        {
            end->data = data;
            end->next = new QueueNode;
            end = end->next;
        }

        T touch()
        {
            return head->next->data;
        }

        T pick()
        {
            T tmp_data = head->next->data;
            tmp = head->next;
            head->next = tmp->next;
            delete tmp;
            return tmp_data;
        }
         bool isEmpty()
         {
             return head->next == end;
         }
};

class ArrayTree
{
private:
    unsigned int data[MAX_DATA_SIZE];
    unsigned int loc[MAX_LOC_SIZE];
    unsigned int size;
    long new_root, lchild, rchild;

    void addChildren()
    {
        cin >> new_root >> lchild >> rchild;
        if(lchild != -1)
        {
            loc[lchild] = loc[new_root] * 2;
            data[loc[lchild]] = lchild;
        }
        if(rchild != -1)
        {
            loc[rchild] = loc[new_root] * 2 + 1;
            data[loc[rchild]] = rchild;
        }
    }

    void printPostOrder(unsigned int new_root_loc)
    {
        if(data[new_root_loc] == 0)
            return;
        printPostOrder(new_root_loc * 2);
        printPostOrder(new_root_loc * 2 + 1);
        cout << data[new_root_loc] << " ";
    }

public:
    ArrayTree()
    {
        data[1] = 1;
        loc[1] = 1;
        for(long i=2; i<MAX_DATA_SIZE; ++i)
            data[i] = 0;
        for(long i=2; i<MAX_LOC_SIZE; ++i)
            loc[i] = 0;
    }

    void input()
    {
        cin >> size;
        for(long i=0; i<size; ++i)
            addChildren();
    }

    void print()
    {
        for(unsigned int i=1; i<=size; ++i)
        {
            if(loc[i]!=0)
                cout << loc[i] << " ";
        }
        cout << endl;
        printPostOrder(1);
        cout << endl;
    }
};

int main(void)
{
    ArrayTree array_tree;
    array_tree.input();
    array_tree.print();
    return 0;
}
