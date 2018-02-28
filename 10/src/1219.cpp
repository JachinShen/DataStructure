#include <iostream>
using namespace std;

class ImportantPair {
private:
    long* data;
    long* tmp;
    long size;
    long re_cnt;
    long findLastGreater(long begin, long end, long key)
    {
        long first = begin, len = end - begin;
        long half, middle;

        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (data[middle] > key)
                len = half;
            else {
                first = middle + 1;
                len = len - half - 1;
            }
        }
        return first;
        /*
            long begin=-1, end=size+1;
            long half;
            while(end - begin > 1)
            {
                half = (begin + end) / 2;
                //if(data[half] == key)
                    //return half;
                if(array[half] > key)
                    begin = half;
                else 
                    end = half;
            }
            return half;
            */
    }
    void print()
    {
        for (long i = 0; i < size; ++i)
            cout << data[i] << " ";
        cout << endl;
    }
    void mergeSort(long begin, long end)
    {
        if (begin >= end)
            return;
        long mid = (begin + end) / 2;
        mergeSort(begin, mid);
        mergeSort(mid + 1, end);
        long x = begin, y = mid + 1, start = begin;
        while (x <= mid && y <= end) {
            if (data[x] < data[y]) {
                tmp[start] = data[x];
                ++start;
                ++x;
            } else {
                long pos = findLastGreater(x, mid + 1, 2 * data[y]);
                re_cnt += mid - pos + 1;
                tmp[start] = data[y];
                ++start;
                ++y;
            }
        }
        while (x <= mid) {
            tmp[start] = data[x];
            ++start;
            ++x;
        }
        while (y <= end) {
            tmp[start] = data[y];
            ++start;
            ++y;
        }
        for (long i = begin; i <= end; ++i)
            data[i] = tmp[i];
        //print();
    }

public:
    ImportantPair(long s)
        : re_cnt(0)
    {
        size = s;
        data = new long[size];
        tmp = new long[size];
    }
    void input()
    {
        for (long i = 0; i < size; ++i)
            cin >> data[i];
    }
    long getReverse()
    {
        mergeSort(0, size - 1);
        return re_cnt;
    }
};

int main(void)
{
    long length;
    cin >> length;
    ImportantPair pair(length);
    pair.input();
    cout << pair.getReverse() << endl;

    return 0;
}
