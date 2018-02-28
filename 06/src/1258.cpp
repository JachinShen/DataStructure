//#define DEBUG
#include <iostream>
using namespace std;

/*
template<class T>
class MyLinar
{
    private:
        struct node
        {
            T data;
            node* next = NULL;
        }
        node* head;
        unsigned long size;
    public:
        MyLinar():head(NULL),size(0){}
        ~MyLinar()
        {
            node *tmp;
            while(head != NULL)
            {
                tmp = head->next;
                delete head;
                head = tmp;
            }
        }

        void create()
        {
            head = new node;
        }

};
*/

class SearchArray
{
    private:
        unsigned long size;
        struct node
        {
            unsigned long data, degree;
            node *lchild = NULL, *rchild = NULL;
            node():degree(1){}
        };
        node *root;
    public:
        SearchArray():size(0), root(NULL){}
        ~SearchArray()
        {
        }

        unsigned long create(unsigned long first_data, unsigned long second_data)
        {
            size = 2;
            root = new node;
            //root->data = (first_data + second_data) / 2;
            root->lchild = new node;
            root->rchild = new node;
            if(second_data < first_data)
            {
                root->rchild->data = first_data;
                root->lchild->data = second_data;
                root->data = second_data;
                return 1;
            }
            else
            {
                root->lchild->data = first_data;
                root->rchild->data = second_data;
                root->data = first_data;
                return 0;
            }
        }

        unsigned long push(unsigned long new_data)
        {
            node* insert = root;
            bool flag = new_data < insert->data;
            unsigned long cnt = 0;
            while(insert->lchild && insert->rchild)
            {
                flag = new_data < insert->data;
                if(flag)
                {
                    cnt += insert->degree;
                    //insert->data = new_data;
                    insert = insert->lchild;
                }
                else
                {
                    ++ insert->degree;
                    insert = insert->rchild;
                }
            }
            insert->lchild = new node;
            insert->rchild = new node;
            //insert->degree = 2;
            flag = new_data < insert->data;
            if(flag)
            {
                insert->lchild->data = new_data;
                insert->rchild->data = insert->data;
                ++cnt;
            }
            else
            {
                insert->rchild->data = new_data;
                insert->lchild->data = insert->data;
            }
            //insert->data += new_data;
            //insert->data /= 2;
            return cnt;
        }
};

class ImprovedLiner
{
    private:
        long *data;
        long size;
        long max_size;
        long search(long new_data)
        {
            long begin = 0, end = size+1;
            long half;
            do
            {
                half = (begin + end) / 2;
                if(data[half] <= new_data)
                    end = half;
                else
                    begin = half;
            }
            while(end - begin > 1);
            return end;
        }

    public:
        void create(long num, long first_data)
        {
            max_size = num;
            data = new long [max_size + 1];
            data[1] = first_data;
            size = 1;
        }

        long push(long new_data)
        {
            long insert = search(new_data);
            for(long i=size; i>=insert; --i)
            {
                data[i+1] = data[i];
            }
            data[insert] = new_data;
            ++size;
            return insert - 1;
        }
};

void swap(long &num1, long &num2)
{
    long tmp = num2;
    num2 = num1;
    num1 = tmp;
}

class Block
{
    private:
        long *data;
        long search(long new_data)
        {
            if(size == 0) return 0;
            long begin = -1, end = size+1;
            long half;
            do
            {
                half = (begin + end) / 2;
                if(data[half] <= new_data)
                    end = half;
                else
                    begin = half;
            }
            while(end - begin > 1);
            return end;
        }

    public:
        long size;
        Block()
        {
            data = new long [150];
            size = 0;
        }
        ~Block(){ if(!data) delete[] data;}
        long push(long new_data)
        {
            long insert = search(new_data);
            for(long i=size; i>=insert; --i)
            {
                data[i+1] = data[i];
            }
            data[insert] = new_data;
            ++size;
            return insert;
        }
};

class BlockArray
{
    private:
        Block *data;
        
    public:
        BlockArray()
        {
            data = new Block[1001]; 
        }
        ~BlockArray(){if(!data) delete[] data; }
        
        long push(long new_data)
        {
            long front_size = 0;
            for(long i=0; i<new_data/100; ++i)
                front_size+=data[i].size;
            return front_size + data[new_data/100].push(new_data);
        }
};

int main(void)
{
    long tree_cnt = 0;
    cin >> tree_cnt;
    long *trees = new long [tree_cnt+1];
    trees[0] = -1;
    for(long i=1; i<=tree_cnt; ++i)
#ifdef DEBUG
        trees[i] = 100001 - i;
#else
        cin >> trees[i];
#endif

    unsigned long unmatch_cnt = 0;
    //ImprovedLiner liner;
    //liner.create(tree_cnt, trees[1]);
    BlockArray blocks;
    for(int i=1; i<=tree_cnt; ++i)
    {
        unmatch_cnt += blocks.push(trees[i]);
        //cout << blocks.push(trees[i]);
    }
    cout << unmatch_cnt;
    cout << endl;

        /*

    SearchArray search;    
    unsigned long unmatch_cnt = search.create(trees[1], trees[2]);
    for(long long i=3; i<=tree_cnt; ++i)
    {
        unmatch_cnt += search.push(trees[i]);
        //cout << search.push(trees[i]) << endl;
    }

    cout << unmatch_cnt << endl;

    unsigned long unmatch_cnt = 0;
    for(long i=1; i<tree_cnt; ++i)
    {
        if(trees[i]>trees[i+1])
        {
            long j=i;
            while(trees[j]>trees[j+1])
            {
                swap(trees[j], trees[j+1]);
                ++unmatch_cnt;
                --j;
            }
        }
    }

    cout << unmatch_cnt << endl;

    */
    return 0;
}
