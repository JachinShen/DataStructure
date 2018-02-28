#include <iostream>
using namespace std;

template < class Type >
class PriorityQueue
{
    private:
        long length;
        Type * array;
        long max_size;

        void doubleSpace()
        {
            Type * tmp = array;

            max_size *= 2;
            array = new Type [max_size];
            for(long i=0; i<=length; ++i)
                array[i] = tmp[i];
            delete [] tmp;
        }
        void percolateDown(long hole)
        {
            long child;
            Type tmp = array[hole];

            for(; hole * 2 <= length; hole = child)
            {
                child = hole * 2;
                if(child != length && array[child + 1] < array[child])
                    child++;
                if(array[child] < tmp)
                    array[hole] = array[child];
                else
                    break;
            }
            array[hole] = tmp;
        }
    public:
        PriorityQueue(int capacity = 1)
        {
            array = new Type[capacity];
            max_size = capacity;
            length = 0;
        }
        ~PriorityQueue()
        {
            if(array != NULL)
                delete [] array;
        }

        bool isEmpty() const
        {
            return length == 0;
        }
        void enQueue(const Type &x)
        {
            if(length == max_size - 1)
                doubleSpace();
            long hole = ++length;
            for(; hole > 1 && x < array[hole / 2]; hole /= 2)
            {
                array[hole] = array[hole / 2];
            }
            array[hole] = x;
        }
        Type deQueue()
        {
            Type min_item = array[1];
            array[1] = array[length--];
            percolateDown(1);
            return min_item;
        }
        Type getHead() const 
        {
            return array[1];
        }
        bool find(Type &elem)
        {
            for(long i=1; i<=length; ++i)
            {
                if(elem == array[i])
                    return true;
            }
            return false;
        }
        long getLength()
        {
            return length;
        }
};

int main(void)
{
    int size;
    cin >> size;
    PriorityQueue<int> queue(size);
    int tmp;
    for(int i=0; i<size; ++i)
    {
        cin >> tmp;
        if(queue.find(tmp))
            continue;
        queue.enQueue(tmp);
    }
    cout << queue.getLength() << endl;
    while(!queue.isEmpty())
    {
        cout << queue.deQueue() << " ";
    }
    cout << endl;
    return 0;
}
