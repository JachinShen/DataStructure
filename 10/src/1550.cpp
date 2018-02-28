#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#define DEBUG
using namespace std;

class MyLinear
{
    private:
        int data[10000];
        int length;
    public:
        MyLinear():length(0){}
        void push_back(int num)
        {
            data[length] = num;
            ++length;
        }
        void clean()
        {
            length = 0;
        }
        int getLength()
        {
            return length;
        }
        int getHead()
        {
            return data[0];
        }
        int getEnd()
        {
            if(length > 0)
                return data[length - 1];
            else
                return -1;
        }
};

int main(void)
{
    srand(1);
    int x_n;
    cin >> x_n;
    int * data = new int [x_n];
    int max_y = 0;
    char ch = 0;
    int x_cnt=0;
    while(ch != ']')
    {
        if(ch >= '0' && ch <='9')
        {
            data[x_cnt] *= 10;
            data[x_cnt] += ch - '0';
        }
        else
        {
            if(ch == ',')
            {
                if(data[x_cnt] > max_y)
                    max_y = data[x_cnt];
                ++x_cnt;
                data[x_cnt] = 0;
            }
        }
        ch = cin.get();
    }
    /*
    for(int i=0; i<x_n; ++i)
        cout << data[i] << " ";
    cout << endl;
       cin.get();
       cin.get();
       for(int i=0; i<x_n; ++i)
       {
       cin >> data[i];
       if(data[i] > max_y)
       max_y = data[i];
       cin.get();
       }
       */
    MyLinear linear;
    long sum = 0;
    for(int i=1; i<=max_y; ++i)
    {
        for(int j=0; j<x_n; ++j)
        {
            if(data[j] >= i)
            {
                linear.push_back(j);
                //cout << j << " ";
            }
            //cout << endl;
        }
        if(linear.getLength() > 1)
        {
            sum += linear.getEnd() - linear.getHead() - linear.getLength() + 1;
            //cout << sum << endl;
        }
        linear.clean();
    }
    cout << sum << endl;
    return 0;
}
