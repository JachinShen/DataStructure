#include <iostream>
using namespace std;

int getS(int N)
{
    if (N % 2 == 0)
        return -N / 2;
    else
        return (N + 1) / 2;
}

int main(void)
{
    int N = 0;
    cout << "Please input N:";
    cin >> N;
    cout << "Sum = " << getS(N) << endl;
    return 0;
}
