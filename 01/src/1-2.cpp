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

int maxSubsequenceSum1(int a[], int size, int& start, int& end)
{
    int maxSum = 0;

    for (int i = 0; i < size; i++)
        for (int j = i; j < size; j++) {
            int thisSum = 0;
            for (int k = i; k <= j; k++)
                thisSum += a[k];
            if (thisSum > maxSum) {
                maxSum = thisSum;
                start = i;
                end = j;
            }
        }
    return maxSum;
}

int maxSubsequenceSum2(int a[], int size, int& start, int& end)
{
    int maxSum = 0;

    for (int i = 0; i < size; i++) {
        int thisSum = 0;
        for (int j = i; j < size; j++) {
            thisSum += a[j];
            if (thisSum > maxSum) {
                maxSum = thisSum;
                start = i;
                end = j;
            }
        }
    }
    return maxSum;
}

int maxSubsequenceSum3(int a[], int size, int& start, int& end)
{
    int maxSum = 0, thisSum = 0, startTmp = 0;
    start = 0;
    end = 0;

    for (int j = 0; j < size; j++) {
        thisSum += a[j];
        if (thisSum < 0)
            thisSum = 0;
        else if (thisSum == a[j])
            startTmp = j;
        if (thisSum > maxSum) {
            maxSum = thisSum;
            start = startTmp;
            end = j;
        }
    }
    return maxSum;
}

int main(void)
{
    int test_array[90000];
    int start = 0, end = 0;
    double last_time = 0;

    srand(tic());

    for (int i = 0; i < 90000; ++i) {
        test_array[i] = rand() % 10000 - 5000;
    }

    last_time = tic();
    cout << "maxSubsequenceSum1 "
         << "maxSum: "
         << maxSubsequenceSum1(test_array, 6, start, end) << endl;

    cout << " start: " << start << " end: " << end
         << " cost time:" << tic() - last_time << endl;

    last_time = tic();
    cout << "maxSubsequenceSum2 "
         << "maxSum: "
         << maxSubsequenceSum2(test_array, 6, start, end) << endl;

    cout << " start: " << start << " end: " << end
         << " cost time:" << tic() - last_time << endl;

    last_time = tic();
    cout << "maxSubsequenceSum3 "
         << "maxSum: "
         << maxSubsequenceSum3(test_array, 6, start, end) << endl;

    cout << " start: " << start << " end: " << end
         << " cost time:" << tic() - last_time << endl;

    return 0;
}
