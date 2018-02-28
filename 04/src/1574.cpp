#include <iostream>
using namespace std;

class MyLoop
{
    private:
        unsigned long size;
        unsigned long head;
    public:
        MyLoop(unsigned long n);
        void loopOnce(unsigned long m);
        void loopK(unsigned long m, unsigned long k);
        unsigned long getData(unsigned long index);
        ~MyLoop();
};

MyLoop::MyLoop(unsigned long n)
{
    size = n;
    head = 0;
}

void MyLoop::loopOnce(unsigned long m)
{
    head = (head + m) % size;
}

void MyLoop::loopK(unsigned long m, unsigned long k)
{
    unsigned long last_m = m;
    for(unsigned long i=0; i<k; ++i)
    {
        last_m = (last_m * 10) % size;
    }
    loopOnce(last_m);
}

unsigned long MyLoop::getData(unsigned long index)
{
    return (head + index) % size;
}

MyLoop::~MyLoop()
{
}

int main(void)
{
    unsigned long n, m, k, x;
    cin >> n >> m >> k >> x;
    for(unsigned long i=0; i<k/3; ++i)
    {
        m = (m * 1000) % n;
    }
    if( k % 3 == 1)
        m = (m * 10) % n;
    if( k % 3 == 2)
        m = (m * 100) % n;
    cout << (m + x) % n << endl;

    //MyLoop question_of_teacher(n);
    //question_of_teacher.loopK(m, k);
    //cout << question_of_teacher.getData(x) << endl;
    return 0;
}
