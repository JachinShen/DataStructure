#include <iostream>
using namespace std;

#define MAX_SIZE 2700

class BigInt
{
    public:
        int * data;
        int max_size;
    public:
        BigInt(int size = MAX_SIZE)
        {
            max_size = size;
            data = new int [max_size];
            for (int i = 0; i < max_size ; ++i) {
                data[i] = 0;
            }
        }
        ~BigInt()
        {
            delete [] data;
        }
        void add(BigInt & add1, BigInt & add2)
        {
            int carry = 0;
            for (int i = 0; i < max_size; ++i) {
                data[i] = add1.data[i] + add2.data[i] + carry;
                if ((carry = data[i] / 10))
                    data[i] %= 10;
            }
        }
        void setValue(int value)
        {
            for (int i = 0; i < max_size && value != 0; ++i) {
                data[i] = value % 10;
                value /= 10;
            }
        }
        void setValue(BigInt & value)
        {
            for (int i = 0; i < max_size; ++i) {
                data[i] = value.data[i];
            }
        }
        void print()
        {
            int i = max_size - 1;
            while(data[i] == 0)
                --i;
            for (; i >= 0; --i) {
                cout << data[i];
            }
            cout << endl;
        }
};

int main(void)
{
    int N;
    cin >> N;
    BigInt two_bit_ctr[4];
    BigInt tmp[4];
    BigInt sum;
    /* 0-00, 1-01, 2-10, 3-11 */
    if (N < 3)
    {
        cout << "0" << endl;
        return 0;
    }
    two_bit_ctr[0].setValue(1);
    two_bit_ctr[1].setValue(2);
    two_bit_ctr[2].setValue(2);
    two_bit_ctr[3].setValue(2);
    for (int i=3; i<N; ++i)
    {
        tmp[0].setValue(two_bit_ctr[2]);
        tmp[1].add(two_bit_ctr[0] , two_bit_ctr[2]);
        tmp[2].add(two_bit_ctr[1] , two_bit_ctr[3]);
        tmp[3].add(two_bit_ctr[1] , two_bit_ctr[3]);
        two_bit_ctr[0].setValue(tmp[0]);
        two_bit_ctr[1].setValue(tmp[1]);
        two_bit_ctr[2].setValue(tmp[2]);
        two_bit_ctr[3].setValue(tmp[3]);
    }
    //two_bit_ctr[0].print();
    //two_bit_ctr[1].print();
    //two_bit_ctr[2].print();
    //two_bit_ctr[3].print();
    sum.add(two_bit_ctr[0], two_bit_ctr[1]);
    //sum.print();
    sum.add(sum, two_bit_ctr[2]);
    //sum.print();
    sum.add(sum, two_bit_ctr[3]);
    sum.print();
    return 0;
}
