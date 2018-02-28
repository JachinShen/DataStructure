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

        void create()
        {
            head = new QueueNode;
            end = head;
        }

        void push(T data)
        {
            tmp = new QueueNode;
            tmp->data = data;
            end->next = tmp;
            end = tmp;
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
             return head->next == NULL;
         }
};

struct Node
{
    long value;
    Node *left_child = NULL, *right_brother = NULL;
};

class Tree
{
    private:
        long node_size;
        Node *nodes;
        Node *root;
        bool *isRoot;

        void printPreOrder(Node* new_root)
        {
            if(new_root == NULL)
                return;
            cout << " " << new_root->value;
            for(Node *p=new_root->left_child; p!=NULL; p=p->right_brother)
            {
                printPreOrder(p);
            }
        }

        void printPostOrder(Node* new_root)
        {
            if(new_root == NULL)
                return;
            for(Node *p=new_root->left_child; p!=NULL; p=p->right_brother)
            {
                printPostOrder(p);
            }
            cout << new_root->value << " ";
        }

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
            long left_child, right_brother;
            cin >> left_child >> right_brother >> nodes[number].value;
            if(left_child > 0)
            {
                nodes[number].left_child = &nodes[left_child];
                isRoot[left_child] = false;
            } 
            if(right_brother > 0)
            {
                nodes[number].right_brother = &nodes[right_brother];
                isRoot[right_brother] = false;
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

        void printPreOrder()
        {
            if(root == NULL)
                return;
            cout << root->value;
            for(Node *p=root->left_child; p!=NULL; p=p->right_brother)
            {
                printPreOrder(p);
            }
            cout << endl;
        }

        void printPostOrder()
        {
            if(root == NULL)
                return;
            for(Node *p=root->left_child; p!=NULL; p=p->right_brother)
            {
                printPostOrder(p);
            }
            cout << root->value;
            cout << endl;
        }

        void printLevel()
        {
            if(root == NULL)
                return;
            MyQueue<Node*> queue;
            queue.create();
            cout << root->value;
            Node *p = NULL;
            for(p=root->left_child; p!=NULL; p=p->right_brother)
            {
                queue.push(p);
            }
            while(!queue.isEmpty())
            {
                p = queue.pick();
                for(Node *q=p->left_child; q!=NULL; q=q->right_brother)
                    queue.push(q);
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
    tree.printPreOrder();
    tree.printPostOrder();
    tree.printLevel();

    return 0;
}
