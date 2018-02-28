#include <iostream>
using namespace std;

bool isPrime(int number)
{
    if (number == 1)
        return false;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0)
            return false;
    }
    return true;
}

int main(void)
{
    int test_number;
    cout << "Please input a number." << endl;
    cin >> test_number;
    if (isPrime(test_number))
        cout << test_number << " is a prime number." << endl;
    else
        cout << test_number << " is not a prime number." << endl;
    return 0;
}
