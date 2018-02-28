#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

double tic()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return ((double)t.tv_sec + ((double)t.tv_usec) / 1000000.);
}

int max1(int array[], int size, int d)
{
    int max = 0, i;
    for (i = 0; i < size; ++i)
        array[i] *= d;
    for (i = 0; i < size; ++i)
        if (array[i] > max)
            max = array[i];
    return max;
}

int max2(int array[], int size, int d)
{
    int max = 0, i;
    for (i = 0; i < size; ++i)
        if (array[i] > max)
            max = array[i];
    return max * d;
}

int main(void)
{
    double last_time = 0;
    int d;
    int test_array1[10000], test_array2[10000];

    srand(tic());

    for (int i = 0; i < 10000; ++i) {
        test_array1[i] = rand() % 10000;
        test_array2[i] = test_array1[i];
    }

    cout << "Please input d:" << endl;
    cin >> d;

    last_time = tic();
    cout << "Function max1 result"
         << "*d : " << max1(test_array1, 10000, d) << endl;
    cout << " cost time:" << tic() - last_time << endl;

    last_time = tic();
    cout << "Function max2 result"
         << "*d : " << max2(test_array2, 10000, d) << endl;
    cout << " cost time:" << tic() - last_time << endl;
    return 0;
}
