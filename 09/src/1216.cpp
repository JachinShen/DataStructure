#include <iostream>
using namespace std;

template < class Type >
class PriorityQueue
{
    private:
        long current_size;
        Type * array;
        long max_size;
        enum
        {
            INSERT,
            FIND,
            DECREASE
        } command;

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
        void find(const Type &x)
        {
            long min_loc;
            bool found = false;
            for(long i=1; i<=current_size; ++i)
            {
                if(array[i] > x)
                {
                    if(!found)
                    {
                        found = true;
                        min_loc = i;
                        continue;
                    }
                    if(array[i] < array[min_loc])
                    {
                        min_loc = i;
                    }
                    else if(array[i] == array[min_loc] && i < min_loc)
                        min_loc = i;
                }
            }
            cout << min_loc << endl;
        }
        void decrease(long i, long v)
        {
            array[i] -= v;
            Type tmp;
            for(; i > 1 && array[i] < array[i / 2]; i /= 2)
            {
                tmp = array[i / 2];
                array[i / 2] = array[i];
                array[i] = tmp;
            }
        }
        void getCommand()
        {
            static char cmd_insert[7] = "insert", cmd_find[5] = "find", cmd_decrease[9] = "decrease";
            char cmd[9] = {0};
            Type cmd_num, cmd_i;
            cin >> cmd;
            if(compareChar(cmd, cmd_insert, 7))
                command = INSERT;
            if(compareChar(cmd, cmd_find, 5))
                command = FIND;
            if(compareChar(cmd, cmd_decrease, 9))
            {
                command = DECREASE;
                cin >> cmd_i;
            }
            cin >> cmd_num;
            switch(command)
            {
                case INSERT: enQueue(cmd_num); break;
                case FIND: find(cmd_num); break;
                case DECREASE: decrease(cmd_i, cmd_num); break;
                default: break;
            }
        }
    public:
        PriorityQueue(int capacity = 1)
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

        bool isEmpty() const
        {
            return current_size == 0;
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
        void input()
        {
            long cmd_cnt;
            cin >> cmd_cnt;
            for(long i=0; i<cmd_cnt; ++i)
            {
                getCommand();
                //print();
            }
        }
        void print()
        {
            for(long i=1; i<=current_size; ++i)
            {
                cout << array[i] << " ";
            }
            cout << endl;
        }
};

int main(void)
{
    PriorityQueue<long> heap;
    heap.input();
    return 0;
}
