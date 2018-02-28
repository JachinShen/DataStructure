#include <iostream>
#include "memory.h"
#include "stdio.h"

using namespace std;

struct Mouse
{
    unsigned long score, strength, id;
    bool operator > (Mouse & m2) {
        if (score == m2.score)
            return id < m2.id;
        return this->score > m2.score;
    }
    bool operator >= (Mouse & m2) {
        if (score == m2.score)
            return id <= m2.id;
        return this->score >= m2.score;
    }
    bool operator < (Mouse & m2) {
        if (score == m2.score)
            return id > m2.id;
        return this->score < m2.score;
    }
    bool operator <= (Mouse & m2) {
        if (score == m2.score)
            return id >= m2.id;
        return this->score <= m2.score;
    }
};

template< class T >
class QuickSort
{
    private:
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
                    if (a[high] <= k) {
                        --high;
                    } else 
                        break;
                }
                if (low < high) {
                    a[low] = a[high];
                    ++low;
                }
                while (low < high) {
                    if (a[low] >= k) {
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
        }
        void quickSort(T a[], long size)
        {
            quickSort(a, 0, size - 1);
        }
};

template< class T >
class MergeSort
{
    private:
        void merge(T a[], long left, long mid, long right)
        {
            T * tmp = new T [right - left + 1];
            long i = left, j = mid, k = 0;
            while (i < mid && j <= right) {
                if (a[i] > a[j]) {
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
        }
        void mergeSort(T a[], long size)
        {
            mergeSort(a, 0, size - 1);
        }
};

void print(Mouse a[], unsigned long size) {
    for (unsigned long i = 0; i < size; ++i) {
        cout << a[i].id << "\t";
    }
    cout << endl;
    for (unsigned long i = 0; i < size; ++i) {
        cout << a[i].score << "\t";
    }
    cout << endl;
    for (unsigned long i = 0; i < size; ++i) {
        cout << a[i].strength << "\t";
    }
    cout << endl;
    cout << endl;
}

void merge(Mouse a[], Mouse winner[], Mouse loser[], unsigned long size)
{
    unsigned long i=0, j=0, k=0;
    while (i < size && j < size) {
        if (winner[i] > loser[j]) {
            a[k++] = winner[i++];
        } else {
            a[k++] = loser[j++];
        }
    }
    while (i < size) {
        a[k++] = winner[i++];
    }
    while (j < size) {
        a[k++] = loser[j++];
    }
}

int main(void)
{
    unsigned long N;
    int R;
    cin >> N >> R;
    Mouse * winner = new Mouse[N];
    Mouse * loser = new Mouse[N];
    unsigned long double_N = N * 2;
    Mouse * mouse = new Mouse [double_N];
    Mouse tmp;
    for (unsigned long i = 0; i < double_N; ++i) {
        scanf("%ld",&mouse[i].score);
        //cin >> mouse[i].score;
        mouse[i].id = i + 1;
    }
    for (unsigned long i = 0; i < double_N; ++i) {
        scanf("%ld",&mouse[i].strength);
        //cin >> mouse[i].strength;
    }
    QuickSort<Mouse> quick_sort;
    quick_sort.quickSort(mouse, double_N);
    //print(mouse, double_N);

    //MergeSort<Mouse> merge_sort;
    unsigned long strength1, strength2;
    for (int i = 0; i < R; ++i) {
        for (unsigned long j = 0, k = 0; j < N; ++j, k += 2) {
            strength1 = mouse[k].strength;
            strength2 = mouse[k + 1].strength;
            if (strength1 == strength2) {
                if (mouse[k].score > mouse[k + 1].score) {
                    ++mouse[k].score;
                    winner[j] = mouse[k];
                    ++mouse[k+1].score;
                    loser[j] = mouse[k+1];
                } else {
                    ++mouse[k].score;
                    loser[j] = mouse[k];
                    ++mouse[k+1].score;
                    winner[j] = mouse[k+1];
                }
            }
            else if (strength1 > strength2) {
                mouse[k].score += 2;
                winner[j] = mouse[k];
                loser[j] = mouse[k+1];
            }
            else {
                mouse[k+1].score += 2;
                winner[j] = mouse[k+1];
                loser[j] = mouse[k];
            }

            while (k > 0 && winner[j] > winner[j-1]){
                tmp = winner[j];
                unsigned long p = j;
                while(p > 0 && tmp > winner[p-1]) {
                    winner[p] = winner[p-1];
                    --p;
                }
                winner[p] = tmp;
            }
            while (k > 0 && loser[j] > loser[j-1]){
                tmp = loser[j];
                unsigned long p = j;
                while(p > 0 && tmp > loser[p-1]) {
                    loser[p] = loser[p-1];
                    --p;
                }
                loser[p] = tmp;
            }
        }
        //print(winner, N);
        //print(loser, N);
        //memcpy(mouse, winner, N * sizeof(Mouse));
        //print(mouse, double_N);
        //memcpy(&mouse[N], loser, N * sizeof(Mouse));
        merge(mouse, winner, loser, N);
        //print(mouse, double_N);
    }

    //print(mouse, double_N);
    for (unsigned long i = 0; i < double_N; ++i) {
        cout << mouse[i].id << " ";
    }
    cout << endl;
    return 0;
}
