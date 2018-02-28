#include <iostream>
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

class Tree
{
private:
    struct Node
    {
        int data;
        Node *lchild, *rchild;
        Node():lchild(NULL), rchild(NULL){}
    };
    Node *data;
    Node *root;
    int size;
    int new_root, lchild, rchild;
    bool *isRoot;
    void getRoot()
    {
        for(int i=1; i<=size; ++i)
        {
            if(isRoot[i])
            {
                root = &data[i];
                return;
            }
        }
    }

    void printLevel()
    {
        getRoot();
        MyQueue<Node*> queue;
        queue.create();
        queue.push(root);
        Node* p;
        while(!queue.isEmpty())
        {
            p = queue.pick();
            cout << p->data << endl;
            if(p->lchild)
                queue.push(p->lchild);
            if(p->rchild)
                queue.push(p->rchild);
        }
    }
public:
    void input()
    {
        cin >> size;
        data = new Node [size+1];
        isRoot = new bool [size+1];
        for(int i=1; i<=size; ++i)
        {
            data[i].data = i;
            isRoot[i] = true;
        }
        for(int i=0; i<size/2; ++i)
        {
            cin >> new_root >> lchild >> rchild;
            data[new_root].lchild = &data[lchild];
            data[new_root].rchild = &data[rchild];
            isRoot[lchild] = false;
            isRoot[rchild] = false;
        }
    }

    void print()
    {
        printLevel();
    }
};

int main(void)
{
    Tree tree;
    tree.input();
    tree.print();

    return 0;
}
