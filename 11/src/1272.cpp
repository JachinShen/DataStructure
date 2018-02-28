#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#define DEBUG
using namespace std;

int main(void)
{
    bool hash_table[200] = {0};
    int n;
    cin >> n;
    int tmp;
    int max = 0;
    for(int i=1; i<=n; ++i)
    {
        cin >> tmp;
        if(tmp > max)
            max = tmp;
        hash_table[tmp] = true;
    }

    int ctr = n;
    while(1)
    {
        bool is_new = false;
        for(int i=max; i>1; --i)
        {
            if(!hash_table[i])
                continue;
            for(int j=i-1; j>0; --j)
            {
                if(!hash_table[j])
                    continue;
                tmp = i/j;
                if(hash_table[tmp])
                    continue;
                hash_table[tmp] = true;
                ++ctr;
                is_new = true;
            }
        }
        if(!is_new)
            break;
    }

    cout << ctr << endl;

    return 0;
}
