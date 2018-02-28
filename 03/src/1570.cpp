#include <iostream>
using namespace std;

long searchByDiv(unsigned long sorted_array[], unsigned long num_to_search, long begin, long end)
{
    long half;
    while(end - begin > 1)
    {
        half = (begin + end) / 2;
        if(sorted_array[half] > num_to_search)
            end = half;
        else
            begin = half;
        //cout << i << " " << j << endl;
        //cout << endl;
    }
    //cout << endl;
    return begin;
}

int main(void)
{
    unsigned long N = 100000, T = 100000;
    cin >> N;
    cin >> T;
    unsigned long *hand_number, *like_number;
    //unsigned long result = 0;
    long begin = -1, end = N, half;
    //unsigned long last_position = 0;
    hand_number = new unsigned long [N];
    like_number = new unsigned long [T];
    for(unsigned long i=0; i<N; ++i)
        cin >> hand_number[i];
        //hand_number[i] = 1234567890+i;
    for(unsigned long i=0; i<T; ++i)
        cin >> like_number[i];
        //like_number[i] = 1234567890+i;
        
    for(unsigned long i=0; i<T; ++i)
    {
        //begin = -1;
        end = N;
        while(end - begin > 1)
        {
            half = (begin + end) / 2;
            if(hand_number[half] > like_number[i])
                end = half;
            else
                begin = half;
            //cout << i << " " << j << endl;
            //cout << endl;
        }

        cout << N - begin - 1 << endl;
    }
    return 0;
}
