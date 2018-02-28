#include <iostream>
using namespace std;

class LIS
{
    private:
        long *data;
        long *before;
        long size;
        long firstMaxBefore(long k, long now_data)
        {
            long begin=-1, end=k+1;
            long half;
            while(end - begin > 1)
            {
                half = (begin + end) / 2;
                if(before[half] == now_data)
                    return half;
                if(before[half] < now_data)
                    begin = half;
                else 
                    end = half;
            }
            return end;
        }

    public:
        LIS():data(NULL){}
        void input()
        {
            cin >> size;
            data = new long [size];
            before = new long [size];
            for(int i=0; i<size; ++i)
            {
                cin >> data[i];
            }
        }

        long getLISSize()
        {
            before[0] = data[0];
            long k=0;
            for(long i=0; i!=size; ++i)
            {
                if(data[i]>before[k])
                    before[++k] = data[i];
                else
                    before[firstMaxBefore(k,data[i])] = data[i];
            }
            return ++k;
            /*
            long max_size = 0;
            long max_length = 0;
            before[0] = 1;
            for(long i=1; i<size; ++i)
            {
                max_length = 0;
                for(long j=i-1; j>=max_length; --j)
                {
                            max_length =
                                data[i]>data[j]
                                &&before[j]>max_length
                                ?
                                before[j]:max_length;
                }
                before[i] = ++max_length;
                max_size =
                    before[i]>max_size
                    ?
                    before[i]:max_size;
            }
            return max_size;
            */
        }
};

int main(void)
{
    LIS lis;
    lis.input();
    cout << lis.getLISSize() << endl;
    return 0;
}
