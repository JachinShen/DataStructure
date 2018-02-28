#include <iostream>
using namespace std;

class MissileIntercept
{
    private:
        unsigned long * data;
        unsigned long * tmp_decrease;
        unsigned long * loc_decrease;
        unsigned long * pre_loc;
        unsigned long * sub_sequence;
        unsigned long size;
        unsigned long firstMinBefore(unsigned long k, unsigned long now_data)
        {
            unsigned long begin=-1, end=k+1;
            unsigned long half;
            while(end - begin > 1)
            {
                half = (begin + end) / 2;
                if(tmp_decrease[half] == now_data)
                    return half;
                if(tmp_decrease[half] > now_data)
                    begin = half;
                else 
                    end = half;
            }
            return end;
        }
        unsigned long firstMaxBefore(unsigned long k, unsigned long now_data)
        {
            unsigned long begin=-1, end=k+1;
            unsigned long half;
            while(end - begin > 1)
            {
                half = (begin + end) / 2;
                if(tmp_decrease[half] == now_data)
                    return half;
                if(tmp_decrease[half] < now_data)
                    begin = half;
                else 
                    end = half;
            }
            return end;
        }
    public:
        void input()
        {
            cin >> size;
            data = new unsigned long [size];
            tmp_decrease = new unsigned long [size];
            loc_decrease = new unsigned long [size];
            pre_loc = new unsigned long [size];
            sub_sequence = new unsigned long [size];
            for(unsigned long i=0; i<size; ++i)
            {
                cin >> data[i];
            }
        }
        unsigned long getLDSSize()
        {
            /*
            long first_nozero = -1;
            for(unsigned long i=0; i!=size; ++i)
            {
                if(data[i] != 0)
                {
                    first_nozero = i;
                    break;
                }
            }
            if(first_nozero == -1)
                return 0;
                */
            tmp_decrease[0] = data[0];
            //loc_decrease[0] = 0;
            //pre_loc[0] = 0;
            unsigned long k=0;
            for(unsigned long i=0; i!=size; ++i)
            {
                if(data[i] == 0)
                    continue;
                if(data[i]<tmp_decrease[k])
                {
                    //pre_loc[i] = loc_decrease[k];
                    ++k;
                    //loc_decrease[k] = i;
                    tmp_decrease[k] = data[i];
                }
                else
                {
                    unsigned long tmp = firstMinBefore(k, data[i]);
                    tmp_decrease[tmp] = data[i];
                    //loc_decrease[tmp] = i;
                    //pre_loc[i] = tmp > 0 ? loc_decrease[tmp-1] : i;
                }
            }
            /*
            unsigned long x = loc_decrease[k];
            for(unsigned long i=k+1;i>0;--i)
            {
                //sub_sequence[i]=data[x];
                data[x] = 0;
                x=pre_loc[x];
            }
            */
            //for(unsigned long i=0; i<=k; ++i)
                //cout << sub_sequence[i];
            //cout << endl;
            return ++k;
        }
        unsigned long getLISSize()
        {
            tmp_decrease[0] = data[0];
            unsigned long k=0;
            for(unsigned long i=0; i!=size; ++i)
            {
                if(data[i]>tmp_decrease[k])
                {
                    ++k;
                    tmp_decrease[k] = data[i];
                }
                else
                {
                    unsigned long tmp = firstMaxBefore(k, data[i]);
                    tmp_decrease[tmp] = data[i];
                }
            }
            return ++k;
        }
        void intercept()
        {
            unsigned long LDS_size = getLDSSize();
            cout << LDS_size << endl;
            /*
            for(i=0; LDS_size!=0; ++i)
                LDS_size = getLDSSize();
            cout << i << endl;
            */
            cout << getLISSize() << endl;
        }
};

int main(void)
{
    MissileIntercept missile_intercept;
    missile_intercept.input();
    missile_intercept.intercept();
    return 0;
}
