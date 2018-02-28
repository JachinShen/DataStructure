#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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
template < class Type >
class AVLTree
{
    private:
        struct AVLNode
        {
            Type data;
            AVLNode *left, *right;
            int height;
            int num;
            AVLNode(const Type &element, AVLNode * lt, AVLNode * rt, int h = 0, int n = 1)
                :data(element), left(lt), right(rt), height(h), num(n){}
        };
        enum
        {
            INSERT,
            DELETE,
            DELETE_LESS_THAN,
            DELETE_GREATER_THAN,
            DELETE_INTERVAL,
            FIND,
            FIND_ITH
        }   command;

        AVLNode * root;
        long ith_cnt;
        bool ith_found;
        bool insert_same;
        bool remove_same;
        long size;

        void insert(const Type &x, AVLNode * &t)
        {
            if(insert_same)
                return;
            if(t == NULL)
            {
                t = new AVLNode(x, NULL, NULL);
                return;
            }
            if(x == t->data)
            {
                ++t->num;
                insert_same = true;
                return;
            }
            if(x < t->data)
            {
                insert(x, t->left);
                if(insert_same)
                    return;
                if(height(t->left) - height(t->right) == 2)
                {
                    if(x < t->left->data)
                        LL(t);
                    else
                        LR(t);
                }
            }
            else if(t->data < x)
            {
                insert(x, t->right);
                if(insert_same)
                    return;
                if(height(t->right) - height(t->left) == 2)
                {
                    if(t->right->data < x)
                        RR(t);
                    else
                        RL(t);
                }
            }
            t->height = max(height(t->left), height(t->right)) + 1;
        }
        bool remove(const Type &x, AVLNode * &t)
        {
            if(remove_same)
                return true;
            bool stop = false;
            int subTree;

            if(t == NULL)
                return true;
            if(t->data == x)
            {
                --t->num;
                if(t->num >= 1)
                {
                    remove_same = true;
                    return true;
                }
            }

            if(x < t->data)
            {
                stop = remove(x, t->left);
                if(remove_same)
                    return true;
                subTree = 1;
            }
            else if(t->data < x)
            {
                stop = remove(x, t->right);
                if(remove_same)
                    return true;
                subTree = 2;
            }
            else if(t->left != NULL && t->right != NULL)
            {
                AVLNode * tmp = t->right;
                while(tmp->left!=NULL)
                    tmp = tmp->left;
                t->data = tmp->data;
                t->num = tmp->num;
                tmp->num = 1;
                stop = remove(t->data, t->right);
                if(remove_same)
                    return true;
                subTree = 2;
            }
            else
            {
                AVLNode * oldNode = t;
                t = (t->left != NULL)? t->left: t->right;
                delete oldNode;
                return false;
            }
            if(stop)
                return true;
            int bf;
            switch(subTree)
            {
                case 1: bf = height(t->left) - height(t->right) + 1;
                        if( bf == 0)
                            return true;
                        if( bf == 1)
                            return false;
                        if( bf == -1)
                        {
                            int bfr = height(t->right->left) - height(t->right->right);
                            switch(bfr)
                            {
                                case 0: RR(t); return true;
                                case -1: RR(t); return false;
                                default: RL(t); return false;
                            }
                        }
                        break;
                case 2: bf = height(t->left) - height(t->right) - 1;
                        if(bf == 0)
                            return true;
                        if(bf == -1)
                            return false;
                        if(bf == 1)
                        {
                            int bfl = height(t->left->left) - height(t->left->right);
                            switch(bfl)
                            {
                                case 0: LL(t); return true;
                                case 1: LL(t); return false;
                                default: LR(t); return false;
                            }
                        }
            }
        }
        void remove_greater_than(const Type &x, AVLNode * &t)
        {
            if(t == NULL)
                return;
            while(t != NULL)
            {
                if(x == t->data)
                {
                    if(t->right == NULL)
                        return;
                    remove_same = false;
                    //remove(t->right->data, t->right);
                    remove(t->right->data, root);
                    remove_same = false;
                }
                if(x > t->data)
                {
                    remove_greater_than(x, t->right);
                    return;
                }
                if(x < t->data)
                {
                    remove_same = false;
                    //remove(t->data, t);
                    remove(t->data, root);
                    remove_same = false;
                }
            }
        }
        void remove_less_than(const Type &x, AVLNode * &t)
        {
            if(t == NULL)
                return;
            while(t != NULL)
            {
                if(x == t->data)
                {
                    if(t->left == NULL)
                        return;
                    remove_same = false;
                    //remove(t->left->data, t->left);
                    remove(t->left->data, root);
                    remove_same = false;
                }
                if(x < t->data)
                {
                    remove_less_than(x, t->left);
                    return;
                }
                if(x > t->data)
                {
                    remove_same = false;
                    //remove(t->data, t);
                    remove(t->data, root);
                    remove_same = false;
                }
            }
        }
        void remove_interval(const Type &x1, const Type &x2, AVLNode * &t)
        {
            if(t == NULL)
                return;
            while(t != NULL)
            {
                if(x1 < t->data && t->data < x2)
                {
                    remove_same = false;
                    //remove(t->data, t);
                    remove(t->data, root);
                    remove_same = false;
                }
                else if(x1 >= t->data)
                {
                    if(t->right == NULL)
                        return;
                    remove_interval(x1, x2, t->right);
                    return;
                }
                else if(t->data >= x2)
                {
                    if(t->left == NULL)
                        return;
                    remove_interval(x1, x2, t->left);
                    return;
                }
            }
        }
        void makeEmpty(AVLNode * &t)
        {
            if(t == NULL)
                return;
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        int height(AVLNode * t) const
        {   return t == NULL ? -1 : t->height;    }
        void LL(AVLNode * &t)
        {
            AVLNode * t1 = t->left;
            t->left = t1->right;
            t1->right = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            t1->height = max(height(t1->left), height(t1->right)) + 1;
            t = t1;
        }
        void RR(AVLNode * &t)
        {
            AVLNode * t1 = t->right;
            t->right = t1->left;
            t1->left = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            t1->height = max(height(t1->left), height(t1->right)) + 1;
            t = t1;
        }
        void LR(AVLNode * &t)
        {
            RR(t->left);
            LL(t);
        }
        void RL(AVLNode * &t)
        {
            LL(t->right);
            RR(t);
        }
        int max(int a, int b)
        {   return ( a > b ) ? a : b;   }
        void find_ith(AVLNode * t)
        {
            if(ith_found)
                return;
            if(t == NULL)
                return;
            find_ith(t->left);
            if(ith_found)
                return;
            if(ith_cnt <= t->num)
            {
                ith_found = true;
                cout << t->data << endl;
                return;
            }
            ith_cnt -= t->num;
            find_ith(t->right);
        }
        void getCommand()
        {
            static char cmd_insert[7] = "insert", cmd_find[5] = "find", cmd_find_ith[9] = "find_ith";
            static char cmd_delete[7] = "delete", cmd_delete_less_than[17] = "delete_less_than";
            static char cmd_delete_greater_than[20] = "delete_greater_than";
            static char cmd_delete_interval[16] = "delete_interval";
            char cmd[20] = {0};
            Type cmd_num1, cmd_num2;
            cin >> cmd;
            if(compareChar(cmd, cmd_insert, 7))
                command = INSERT;
            if(compareChar(cmd, cmd_find, 5))
                command = FIND;
            if(compareChar(cmd, cmd_find_ith, 9))
                command = FIND_ITH;
            if(compareChar(cmd, cmd_delete, 7))
                command = DELETE;
            if(compareChar(cmd, cmd_delete_less_than, 17))
                command = DELETE_LESS_THAN;
            if(compareChar(cmd, cmd_delete_greater_than, 20))
                command = DELETE_GREATER_THAN;
            if(compareChar(cmd, cmd_delete_interval, 16))
            {
                command = DELETE_INTERVAL;
                cin >> cmd_num1;
            }
            cin >> cmd_num2;
            switch(command)
            {
                case INSERT: insert(cmd_num2); break;
                case DELETE: remove(cmd_num2); break;
                case FIND: if(find(cmd_num2))
                               cout << "Y" << endl;
                           else
                               cout << "N" << endl;
                           break;
                case FIND_ITH: find_ith(cmd_num2); break;
                case DELETE_GREATER_THAN: remove_greater_than(cmd_num2); break;
                case DELETE_LESS_THAN: remove_less_than(cmd_num2); break;
                case DELETE_INTERVAL: remove_interval(cmd_num1, cmd_num2); break;
                default: break;
            }
        }
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
        AVLTree( AVLNode * t = NULL)
        {
            root = t;
            size = (t == NULL)? 0: 1;
        }
        ~AVLTree()
        {   makeEmpty(root);    }
        bool find (const Type &x) const
        {
            AVLNode * t = root;

            while(t != NULL && t->data != x)
                if(t->data > x)
                    t = t->left;
                else
                    t = t->right;

            if(t == NULL)
                return false;
            else
                return true;
        }
        void insert( const Type &x)
        {   
            insert_same = false;
            insert(x, root);
        }
        void remove( const Type &x)
        {   
            remove_same = false;
            remove(x, root);
            remove_same = false;
        }
        void remove_greater_than( const Type &x)
        {
            remove_greater_than(x, root);
        }
        void remove_less_than( const Type &x)
        {
            remove_less_than(x, root);
        }
        void remove_interval( const Type &x1, const Type &x2)
        {
            remove_interval(x1, x2, root);
        }
        void find_ith(const long ith)
        {
            ith_cnt = ith;
            ith_found = false;
            find_ith(root);
            if(!ith_found)
                cout << "N" << endl;
        }
        void printLevel()
        {
            MyQueue<AVLNode*> queue;
            queue.create();
            queue.push(root);
            AVLNode* p;
            while(!queue.isEmpty())
            {
                p = queue.pick();
                cout << p->data << endl;
                if(p->left)
                    queue.push(p->left);
                if(p->right)
                    queue.push(p->right);
            }
        }
        void input()
        {
            long cmd_cnt;
            cin >> cmd_cnt;
            for(long i=0; i<cmd_cnt; ++i)
                getCommand();
        }
        void test()
        {
            srand(1);
            Type cmd_num1, cmd_num2;
            long cnt;
            cin >> cnt;
            for(long i=0; i<cnt; ++i)
            {
                cout << i;
                if(i >= 3783569)
                    cout << "Occupy" << endl;
                cmd_num1 = rand() % 100;
                cmd_num2 = rand() % 100;
                switch(rand() % 8)
                {
                    case 1: insert(cmd_num2); break;
                    case 2: remove(cmd_num2); break;
                    case 3: if(find(cmd_num2))
                                   cout << "Y" << endl;
                               else
                                   cout << "N" << endl;
                               break;
                    case 4: find_ith(cmd_num2); break;
                    case 5: remove_greater_than(cmd_num2); break;
                    case 6: remove_less_than(cmd_num2); break;
                    case 7: remove_interval(cmd_num1, cmd_num2); break;
                    default: break;
                }
            }
        }
};

int main(void)
{
    AVLTree<long> avltree;
    //avltree.test();
    avltree.input();

    return 0;
}
