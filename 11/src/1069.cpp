#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#define DEBUG

using namespace std;

int main(void)
{

    int n;
    long m;
    long * Ai;
    int * Ci;
    int * left_coins;
    while(1)
    {
        cin >> n >> m;
        if(n == 0 && m == 0)
            return 0;
        Ai = new long [n];
        Ci = new int [n];
        for(int i=0; i<n; ++i)
            cin >> Ai[i];
        for(int i=0; i<n; ++i)
            cin >> Ci[i];

        left_coins = new int [m+1];
        for(long i=0; i<=m; ++i)
            left_coins[i] = -1;

        left_coins[0] = 0;
        for(int i=0; i<n; ++i)
        {
            for(long j=0; j<=m; ++j)
            {
                if(left_coins[j] >= 0)
                {
                    left_coins[j] = Ci[i];
                }
                else if(j < Ai[i] || left_coins[j - Ai[i]] <= 0)
                {
                    left_coins[j] = -1;
                }
                else
                {
                    left_coins[j] = left_coins[j - Ai[i]] - 1;
                }
            }
        }

        /*
           for(long i=0; i<=n; ++i)
           {
           for(long j=0; j<=m; ++j)
           {
           cout << left_coins[i][j] << " ";
           }
           cout << endl;
           }
           */

        long sum = 0;
        for(long i=1; i<=m; ++i)
        {
            if(left_coins[i] != -1)
                ++sum;
        }
        cout << sum << endl;
        delete [] Ai;
        delete [] Ci;
        delete [] left_coins;
    }

    return 0;
}
