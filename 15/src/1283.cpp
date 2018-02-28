#include <iostream>
using namespace std;

class Union
{
public:
    Union (int n) {
        prev = new int [n + 1];
        size = n;
        for (int i = 1; i <= n; ++i) {
            prev[i] = i;
        }
    }
    ~Union () {
        if (prev)
            delete [] prev;
    }

    int find(int x) {
        int r = x;
        while (r != prev[r])
            r = prev[r];
        int i = x, j;
        while (i != r) {
            j = prev[i];
            prev[i] = r;
            i = j;
        }
        return r;
    }

    void join(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            prev[fx] = fy;
        }
    }

    int contourCount() {
        int ctr = 0;
        for (int i = 1; i <= size; ++i) {
            if (prev[i] == i)
                ++ctr;
        }
        return ctr;
    }

private:
    int * prev;
    int size;
};

class BigTwo
{
public:
    BigTwo (int power) {
        num[0] = 1;
        length = 1;
        int len;
        int carry;
        int tmp;
        for (int i = 0; i < power; ++i) {
            carry = 0;
            len = length;
            for (int j = 0; j < len; ++j) {
                tmp = num[j] * 2 + carry;
                num[j] = tmp % 10;
                carry = tmp / 10;
            }
            if (carry != 0) {
                num[length] = carry;
                ++length;
            }
        }
    }
    void print() {
        for (int i = length - 1; i >= 0; --i) {
            cout << num[i];
        }
        cout << endl;
    }
    ~BigTwo (){}

private:
    int num[350];
    int length;
};

int main(void)
{
    int n, m;
    cin >> n >> m;
    int p, q;
    Union chemical(n);
    for (int i = 0; i < m; ++i) {
        cin >> p >> q;
        chemical.join(p, q);
    }

    BigTwo result(n - chemical.contourCount());
    result.print();
    
    return 0;
}
