#include <iostream>

using namespace std;

template < class Type >
class PriorityQueue
{
    private:
        long length;
        Type * array;
        long max_size;
        long cmp_ctr;

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
                if(child != length) {
                    ++cmp_ctr;
                    if(array[child + 1] < array[child]) {
                        child++;
                    }
                }
                ++cmp_ctr;
                if(array[child] < tmp) {
                    array[hole] = array[child];
                }
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
            cmp_ctr = 0;
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
            for(;hole > 1; hole /= 2)
            {
                ++cmp_ctr;
                if(x < array[hole / 2]) {
                    array[hole] = array[hole / 2];
                } else {
                    break;
                }
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
        long getLength()
        {
            return length;
        }
        long getCmpCtr()
        {
            return cmp_ctr;
        }
};

template< class T >
class MergeSort
{
    private:
        long cmp_ctr;

        void merge(T a[], long left, long mid, long right)
        {
            T * tmp = new T [right - left + 1];
            long i = left, j = mid, k = 0;
            while (i < mid && j <= right) {
                ++cmp_ctr;
                if (a[i] < a[j]) {
                    tmp[k++] = a[i++];
                } else {
                    tmp[k++] = a[j++];
                }
            }
            while (i < mid) {
                tmp[k++] = a[i++];
            }
            while (j <= right) {
                tmp[k++] = a[j++];
            }
            for (i = 0, k = left; k <= right; ) {
                a[k++] = tmp[i++];
            }
            delete [] tmp;
        }

        void mergeSort(T a[], long left, long right)
        {
            long mid = (left + right - 1) / 2;
            if(left == right)
                return;
            mergeSort(a, left, mid);
            mergeSort(a, mid + 1, right);
            merge(a, left, mid + 1, right);
        }

    public:
        MergeSort()
        {
            cmp_ctr = 0;
        }
        void mergeSort(T a[], long size)
        {
            mergeSort(a, 0, size - 1);
        }
        long getCmpCtr()
        {
            return cmp_ctr;
        }
};

template< class T >
class QuickSort
{
    private:
        long cmp_ctr;

        void quickSort(T a[], long low, long high)
        {
            long mid;
            if (low >= high)
                return;
            mid = divide(a, low, high);
            quickSort(a, low, mid - 1);
            quickSort(a, mid + 1, high);
        }
        long divide(T a[], long low, long high)
        {
            T k = a[low];
            do {
                while (low < high) {
                    ++cmp_ctr;
                    if (a[high] >= k) {
                        --high;
                    } else 
                        break;
                }
                if (low < high) {
                    a[low] = a[high];
                    ++low;
                }
                while (low < high) {
                    ++cmp_ctr;
                    if (a[low] <= k) {
                        ++low;
                    } else 
                        break;
                }
                if (low < high) {
                    a[high] = a[low];
                    --high;
                }
            } while (low != high);
            a[low] = k;
            return low;
        }
    public:
        QuickSort()
        {
            cmp_ctr = 0;
        }
        void quickSort(T a[], long size)
        {
            quickSort(a, 0, size - 1);
        }
        long getCmpCtr()
        {
            return cmp_ctr;
        }
};

int main(void)
{
    long N, k;
    cin >> N >> k;
    long tmp;
    if (k == 1) {
        PriorityQueue<long> sort_heap(N);
        for (long i = 0; i < N; i++) {
            cin >> tmp;
            sort_heap.enQueue(tmp);
        }
        for (long i = 0; i < N; i++) {
            sort_heap.deQueue();
        }
        cout << sort_heap.getCmpCtr() << endl;
    }
    if (k == 2) {
        MergeSort<long> merge_sort;
        long * array = new long [N];
        for (long i = 0; i < N; i++) {
            cin >> array[i];
        }
        merge_sort.mergeSort(array, N);
        cout << merge_sort.getCmpCtr() << endl;
    }
    if (k == 3) {
        QuickSort<unsigned long> quick_sort;
        unsigned long * array = new unsigned long [N];
        for (long i = 0; i < N; i++) {
            cin >> array[i];
        }
        quick_sort.quickSort(array, N);
        cout << quick_sort.getCmpCtr() << endl;
    }
    return 0;
}
