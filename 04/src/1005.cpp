#include <iostream>
using namespace std;

class Sudoku
{
    private:
        int data[9][9];
        bool checkCols();
        bool checkRows();
        bool checkBlocks();

    public:
        Sudoku();
        void getData();
        void print();
        bool check();
};

Sudoku::Sudoku(){}

void Sudoku::getData()
{
    for(int i=0; i<9; ++i)
        for(int j=0; j<9; ++j)
            cin >> data[i][j];
}

void Sudoku::print()
{
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j)
            cout << data[i][j];
        cout << endl;
    }
}

bool Sudoku::checkCols()
{
    for(int j=0; j<9; ++j)
    {
        bool isOccupied[9] = {0};
        for(int i=0; i<9; ++i)
            isOccupied[data[i][j] - 1] = true;
        for(int n=0; n<9; ++n)
            if(!isOccupied[n])
                return false;
    }
    return true;
}

bool Sudoku::checkRows()
{
    for(int i=0; i<9; ++i)
    {
        bool isOccupied[9] = {0};
        for(int j=0; j<9; ++j)
            isOccupied[data[i][j] - 1] = true;
        for(int n=0; n<9; ++n)
            if(!isOccupied[n])
                return false;
    }
    return true;
}

bool Sudoku::checkBlocks()
{
    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
        {
            bool isOccupied[9] = {0};
            for(int p=0; p<3; ++p)
                for(int q=0; q<3; ++q)
                    isOccupied[data[3*i+p][3*j+q] - 1] = true;
            for(int n=0; n<9; ++n)
                if(!isOccupied[n])
                    return false;
        }
    return true;


}

bool Sudoku::check()
{
    //cout << checkCols() <<endl;
    //cout << checkRows() <<endl;
    //cout << checkBlocks() <<endl;
    return checkCols()&&checkRows()&&checkBlocks();
}

int main(void)
{
    int count = 0;
    cin >> count;

    Sudoku *sudoku;
    sudoku = new Sudoku[count];
    for(int i=0; i<count; ++i)
    {
        sudoku[i].getData();
    }
    for(int i=0; i<count; ++i)
    {
        if(sudoku[i].check())
            cout << "Right" << endl;
        else
            cout << "Wrong" << endl;
    }
    delete sudoku;
    return 0;
}
