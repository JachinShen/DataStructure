#include <iostream>
using namespace std;

int main(void)
{
    int money_cost[12];
    int money_hand=0, money_receive = 300, money_store=0;
    for(int i=0; i<12; ++i)
        cin >> money_cost[i];

    for(int month=0; month<12; ++month)
    {
        money_hand += money_receive;
        money_hand -= money_cost[month];
        if(money_hand < 0)
        {
            cout << "-" << month+1 <<endl;
            return 0;
        }
        while(money_hand >= 100)
        {
            money_store += 100;
            money_hand -= 100;
        }

    }
    cout << money_hand + 1.2 * money_store << endl;
    return 0;
}
