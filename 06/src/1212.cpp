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

struct Node
{
    long value;
    Node *left_child = NULL, *right_child = NULL;
};

class Tree
{
    private:
        long node_size;
        Node *nodes;
        Node *root;
        bool *isRoot;

    public:
        Tree():nodes(NULL){}
        ~Tree()
        {
            if(nodes != NULL)
                delete[] nodes;
        }
        
        void create(long node_number)
        {
            node_size = node_number;
            nodes = new Node[node_number + 1];
            isRoot = new bool[node_number + 1];
            //tree_array = new long[node_number + 1];
            isRoot[0] = false;
            for(long i=1; i<=node_size; ++i)
            {
                isRoot[i] = true;
                //tree_array[i] = 0;
            }
        }

        void addNode(long number)
        {
            long left_child, right_child;
            cin >> left_child >> right_child >> nodes[number].value;
            if(left_child > 0)
            {
                nodes[number].left_child = &nodes[left_child];
                isRoot[left_child] = false;
            } 
            if(right_child > 0)
            {
                nodes[number].right_child = &nodes[right_child];
                isRoot[right_child] = false;
            }
        }

        void getRoot()
        {
            for(long i=1; i<=node_size; ++i)
            {
                if(isRoot[i])
                {
                    root = &nodes[i];
                    return;
                }
            }
        }

        void printLevel()
        {
            if(root == NULL)
                return;
            MyQueue<Node*> queue;
            queue.create();
            cout << root->value;
            Node *p = NULL;
            if(root->left_child != NULL)
                queue.push(root->left_child);
            if(root->right_child != NULL)
                queue.push(root->right_child);
            while(!queue.isEmpty())
            {
                p = queue.pick();
                if(p->left_child != NULL)
                    queue.push(p->left_child);
                if(p->right_child != NULL)
                    queue.push(p->right_child);
                cout << " " << p->value;
            }
            cout << endl;
        }
};

int main(void)
{
    Tree tree;
    long node_num = 0;
    cin >> node_num;
    tree.create(node_num);
    for(long i=1; i<=node_num; ++i)
    {
        tree.addNode(i);
    }
    tree.getRoot();
    tree.printLevel();

    return 0;
}
