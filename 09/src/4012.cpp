#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define DEBUG
using namespace std;

template < class Type >
class PriorityQueue
{
    private:
        long current_size;
        Type * array;
        long max_size;

        void doubleSpace()
        {
            Type * tmp = array;

            max_size *= 2;
            array = new Type [max_size];
            for(long i=0; i<=current_size; ++i)
                array[i] = tmp[i];
            delete [] tmp;
        }
        void percolateDown(long hole)
        {
            long child;
            Type tmp = array[hole];

            for(; hole * 2 <= current_size; hole = child)
            {
                child = hole * 2;
                if(child != current_size && array[child + 1] < array[child])
                    child++;
                if(array[child] < tmp)
                    array[hole] = array[child];
                else
                    break;
            }
            array[hole] = tmp;
        }
    public:
        PriorityQueue(long capacity = 100)
        {
            array = new Type[capacity];
            max_size = capacity;
            current_size = 0;
        }
        ~PriorityQueue()
        {
            if(array != NULL)
                delete [] array;
        }

        long getSize() const
        {
            return current_size;
        }
        void enQueue(const Type &x)
        {
            if(current_size == max_size - 1)
                doubleSpace();
            long hole = ++current_size;
            for(; hole > 1 && x < array[hole / 2]; hole /= 2)
            {
                array[hole] = array[hole / 2];
            }
            array[hole] = x;
        }
        Type deQueue()
        {
            Type min_item = array[1];
            array[1] = array[current_size--];
            percolateDown(1);
            return min_item;
        }
        Type getHead() const 
        {
            return array[1];
        }
};

int main(void)
{
    long size;
    cin >> size;
    unsigned long tmp;
    unsigned long min1, min2;
    unsigned long sum = 0;
    PriorityQueue<unsigned long> fruits(size);
    for(long i=0; i<size; ++i)
    {
        cin >> tmp;
        fruits.enQueue(tmp);
    }
    //cout << fruits.getSize() << endl;
    while(fruits.getSize() > 1)
    {
        min1 = fruits.deQueue();
        min2 = fruits.deQueue();
        tmp = min1 + min2;
        sum += tmp;
        fruits.enQueue(tmp);
    }
    cout << sum << endl;
    return 0;
}

/*
class hfTree
{
    private:
        struct Node
        {
            unsigned long weight;
            long parent, left, right;
            Node():weight(0), parent(0), left(0), right(0){}
        };
        Node * elem;
        long length;

    public:
        hfTree(long size)
        {
            elem = new Node[2 * size];
            length = 2 * size;
            for(long i=size; i<length; ++i)
                cin >> elem[i].weight;
        }
        void getMin()
        {
            unsigned long min1, min2;
            long min1_loc, min2_loc;

            for(long i=length/2 - 1; i>0; --i)
            {
                min1 = min2 = 32767;
                min1_loc = min2_loc = 0;
                for(long j=i+1; j<length; ++j)
                {
                    if(elem[j].parent == 0)
                    {
                        if(elem[j].weight < min1)
                        {
                            min2 = min1;
                            min1 = elem[j].weight;
                            min2_loc = min1_loc;
                            min1_loc = j;
                        }
                        else if(elem[j].weight < min2)
                        {
                            min2 = elem[j].weight;
                            min2_loc = j;
                        }
                    }
                }
                elem[i].weight = min1 + min2;
                elem[i].left = min1_loc;
                elem[i].right = min2_loc;
                elem[min1_loc].parent = i;
                elem[min2_loc].parent = i;
            }
        }
        void prlong()
        {
#ifdef DEBUG
            for(long i=0; i<length; ++i)
                cout << elem[i].weight << " ";
            cout << endl;
#endif
            unsigned long sum = 0;
            for(long i=0; i<length/2; ++i)
                sum += elem[i].weight;
            cout << sum << endl;
        }
        ~hfTree()
        {
            if(elem)
                delete [] elem;
        }
};

int main(void)
{
    long size;
    cin >> size;
    hfTree hf_tree(size);
    hf_tree.getMin();
    hf_tree.prlong();

    return 0;
}
*/
