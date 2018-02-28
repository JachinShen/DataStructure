#include <iostream>
#define MAX_SIZE 20
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

class BernouliTree
{
    private:
        struct Node
        {
            long data;
            Node *child = NULL, *brother = NULL;
            Node(long new_data):data(new_data){};
        };
        Node *roots[MAX_SIZE];
        enum
        {
            INSERT,
            DELETE,
            MIN
        }   state;
        char command[7];

        bool compareChar(char ch1[], char ch2[], int size)
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


    public:
        BernouliTree()
        {
            for(int i=0; i<MAX_SIZE; ++i)
                roots[i] = NULL;
        }

        void push(long new_data)
        {
            Node *new_root = new Node(new_data);
            Node *new_child = NULL;
            Node *tmp = NULL;
            for(int i=0; i<MAX_SIZE; ++i)
            {
                if(roots[i] == NULL)
                {
                    roots[i] = new_root;
                    break;
                }
                else
                {
                    if(new_root->data < roots[i]->data)
                    {
                        new_child = roots[i];
                    }
                    else
                    {
                        new_child = new_root;
                        new_root = roots[i];
                    }

                    if(new_root->child != NULL)
                    {
                        tmp = new_root->child;
                        new_root->child = new_child;
                        new_child->brother = tmp;
                    }
                    else
                    {
                        new_root->child = new_child;
                    }
                    roots[i] = NULL;
                }
            }
        }

        long getMin()
        {
            long min;
            for(int i=0; i<MAX_SIZE; ++i)
            {
                if(roots[i] != NULL)
                {
                    min = roots[i]->data;
                    break;
                }
            }
            for(int i=0; i<MAX_SIZE; ++i)
            {
                if(roots[i] == NULL)
                    continue;
                if(roots[i]->data < min)
                    min = roots[i]->data;
            }
            return min;
        }

        void deleteMin()
        {
            int min_index, min;
            for(int i=0; i<MAX_SIZE; ++i)
            {
                if(roots[i] != NULL)
                {
                    min = roots[i]->data;
                    min_index = i;
                    break;
                }
            }
            for(int i=0; i<MAX_SIZE; ++i)
            {
                if(roots[i] == NULL)
                    continue;
                if(roots[i]->data < min)
                {
                    min = roots[i]->data;
                    min_index = i;
                }
            }

            Node* childs[MAX_SIZE]={0};
            int childs_cnt = 0;
            Node* p = roots[min_index]->child;
            Node *new_root, *new_child, *tmp;
            for(childs_cnt=0; childs_cnt<MAX_SIZE; ++childs_cnt)
            {
                if( p == NULL)
                    break;
                childs[childs_cnt] = p;
                p = p->brother;
                childs[childs_cnt]->brother = NULL;
            }
            --childs_cnt;
            delete roots[min_index];
            roots[min_index] = NULL;

            for(int i=childs_cnt; i>=0; --i)
            {
                new_root = childs[i];
                for(int j=childs_cnt - i; j<MAX_SIZE; ++j)
                {
                    if(roots[j] == NULL)
                    {
                        roots[j] = new_root;
                        break;
                    }
                    if(new_root->data < roots[j]->data)
                    {
                        new_child = roots[j];
                    }
                    else
                    {
                        new_child = new_root;
                        new_root = roots[j];
                    }
                    if(new_root->child != NULL)
                    {
                        tmp = new_root->child;
                        new_root->child = new_child;
                        new_child->brother = tmp;
                    }
                    else
                    {
                        new_root->child = new_child;
                    }
                    roots[j] = NULL;
                }
            }

        }

        void print()
        {
            MyQueue<Node*> queue;
            queue.create();
            for(int i=0; i<MAX_SIZE; ++i)
            {
                if(roots[i] == NULL)
                    continue;
                Node *p = NULL;
                queue.push(roots[i]);
                while(!queue.isEmpty())
                {
                    p = queue.pick();
                    cout << " " << p->data;
                    for(Node* q=p->child; q; q=q->brother)
                    {
                        queue.push(q);
                    }
                }
                cout << endl;
            }
        }

        void getCmd()
        {
            static char cmd_insert[7] = "insert", cmd_delete[7] = "delete", cmd_min[4] = "min";
            long cmd_arg;
            long steps = 0;
            cin >> steps;
            for(long i=0; i<steps; ++i)
            {
                cin >> command;
                if(compareChar(command, cmd_insert, 7))
                    state = INSERT;
                if(compareChar(command, cmd_delete, 7))
                    state = DELETE;
                if(compareChar(command, cmd_min, 4))
                    state = MIN;
                switch(state)
                {
                    case INSERT: cin >> cmd_arg; push(cmd_arg); break;
                    case DELETE: deleteMin(); break;
                    case MIN: cout << getMin() << endl; break;
                    default: break;
                }
            }

        }

};

int main(void)
{
    BernouliTree bernouli_tree;
    bernouli_tree.getCmd();
    /*
    for(long i=0; i<190; ++i)
    {
        bernouli_tree.push(i);
        bernouli_tree.print();
        cout << "*****" << bernouli_tree.getMin() <<  endl;
    }
    for(long i=0; i<190; ++i)
    {
        bernouli_tree.deleteMin();
        bernouli_tree.print();
        cout << "*****" << bernouli_tree.getMin() <<  endl;
    }
    */

    return 0;
}

