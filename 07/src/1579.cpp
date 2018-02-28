#include <iostream>
using namespace std;


class LCS
{
    private:
        char *data1, *data2;           
        int length1, length2;
        int **mat;
        int Max2(int n1, int n2)
        {
            return n1>n2?n1:n2;
        }

        int Max(int n1, int n2, int n3)
        {
            return Max2(n1,Max2(n2, n3));
        }
    public:
        LCS():data1(NULL),data2(NULL){}
        void input()
        {
            cin >> length1 >> length2;
            data1 = new char [length1];
            data2 = new char [length2];
            for(int i=0; i<length1; ++i)
                cin >> data1[i];
            for(int i=0; i<length2; ++i)
                cin >> data2[i];
            mat = new int* [length2+1];
            for(int i=0; i<=length2; ++i)
            {
                mat[i] = new int [length1+1];
                for(int j=0; j<=length1; ++j)
                    mat[i][j] = 0;
            }
        }

        int getLCS()
        {
            int max_size = 0;
            for(int i=1; i<=length2; ++i)
            {
                for(int j=1; j<=length1; ++j)
                {
                    if(data2[i-1] == data1[j-1])
                    {
                        mat[i][j] = Max(++mat[i-1][j-1],
                                mat[i][j-1],mat[i-1][j]);
                        if(max_size < mat[i][j])
                            max_size = mat[i][j];
                    }
                    else
                    {
                        mat[i][j] = Max(mat[i-1][j-1],
                                mat[i][j-1],mat[i-1][j]);
                    }
                }
            }
            return max_size;
        }
};

int main(void)
{
    LCS lcs;
    lcs.input();
    cout << lcs.getLCS() << endl;
    return 0;
}
