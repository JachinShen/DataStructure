#include <iostream>
using namespace std;

template < class T >
class MyLinear
{
    private:
        long max_size, length, front;
        T * data;

    public:
        void create(long size)
        {
            max_size = size;
            data = new T [max_size];
            length = 0;
            front = 0;
        }

        void push_back(T &elem)
        {
            data[length] = elem;
            length++;
        }
        
        T getHead()
        {
            return data[front];
        }

        void pop_head()
        {
            ++front;
        }

        bool isEmpty()
        {
            return front == length;
        }
};

class Merge
{
    private:
        long array1_size, array2_size, merged_size;
        MyLinear<int> array1, array2;

    public:
        void input()
        {
            cin >> array1_size;
            cin >> array2_size;
            merged_size = array1_size + array2_size;
            array1.create(array1_size);
            array2.create(array2_size);
            int tmp;
            for(long i=0; i<array1_size; ++i)
            {
                cin >> tmp;
                array1.push_back(tmp);
            }
            for(long i=0; i<array2_size; ++i)
            {
                cin >> tmp;
                array2.push_back(tmp);
            }
        }

        void merge()
        {
            for(int i=0; i<merged_size; ++i)
            {
                if(array1.isEmpty())
                {
                    while(!array2.isEmpty())
                    {
                        cout << array2.getHead() << " ";
                        array2.pop_head();
                    }
                    break;
                }
                if(array2.isEmpty())
                {
                    while(!array1.isEmpty())
                    {
                        cout << array1.getHead() << " ";
                        array1.pop_head();
                    }
                    break;
                }
                if(array1.getHead() > array2.getHead())
                {
                    cout << array2.getHead() << " ";
                    array2.pop_head();
                }
                else
                {
                    cout << array1.getHead() << " ";
                    array1.pop_head();
                }
            }
            cout << endl;
        }
};

int main(void)
{
    Merge merge;
    merge.input();
    merge.merge();

    return 0;
}
