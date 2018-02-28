#include <iostream>
using namespace std;

class Tree
{
    private:
        char data[1002];
        char front[27];
        char middle[27];

        void recoverLeft(int root_position, char new_front[], char new_middle[], int size)
        {
            data[root_position * 2 - 1] = new_front[0];
            if(size == 1)
                return;
            else
            {
                int new_root_middle = searchChar(new_front[0], new_middle, 27) + 1;
                int new_left_front = searchNewFront(new_middle, new_root_middle - 1, new_front, 27);
                int new_right_front = searchNewFront(new_middle + new_root_middle, size - new_root_middle, new_front, 27);
                if(new_left_front > 0)
                    recoverLeft(root_position * 2, new_front + new_left_front, new_middle, new_root_middle - 1);
                if(new_right_front > 0)
                    recoverRight(root_position * 2, new_front + new_right_front, new_middle + new_root_middle, size - new_root_middle);
            }
        }

        void recoverRight(int root_position, char new_front[], char new_middle[], int size)
        {
            data[root_position * 2 + 1 - 1] = new_front[0];
            if(size == 1)
                return;
            else
            {
                int new_root_middle = searchChar(new_front[0], new_middle, 27) + 1;
                int new_left_front = searchNewFront(new_middle, new_root_middle - 1, new_front, 27);
                int new_right_front = searchNewFront(new_middle + new_root_middle, size - new_root_middle, new_front, 27);
                if(new_left_front > 0)
                    recoverLeft(root_position * 2 + 1, new_front + new_left_front, new_middle, new_root_middle - 1);
                if(new_right_front > 0)
                    recoverRight(root_position * 2 + 1, new_front + new_right_front, new_middle + new_root_middle, size - new_root_middle);
            }
        }

        int searchChar(char ch_to_search, char chs_search_from[], int size)
        {
            for(int i=0; i<size; ++i)
            {
                if(ch_to_search == chs_search_from[i])
                    return i;
            }
            return -1;
        }

        int searchNewFront(char new_middle[], int new_middle_size, char new_front[], int size)
        {
            for(int i=0; i<size; ++i)
            {
                for(int j=0; j<new_middle_size; ++j)
                {
                    if(new_middle[j] == new_front[i])
                            return i;
                }
            }
            return -1;
        }

        int getLength(char str[])
        {
            for(int i=0; i<1002; ++i)
            {
                if(str[i] == 0)
                    return i;
            }
            return -1;
        }
    public:
        void init()
        {
            for(int i=0; i<27; ++i)
            {
                front[i] = 0;
                middle[i] = 0;
            }
            for(int i=0; i<1002; ++i)
            {
                data[i] = 0;
            }
        }
        void getData()
        {
            cin >> front;
            cin >> middle;
        }
        void recover()
        {
            data[0] = front[0];
            int size = getLength(front);
            int new_root_middle = searchChar(front[0], middle, 27) + 1;
            int new_left_front = searchNewFront(middle, new_root_middle - 1, front, 27);
            int new_right_front = searchNewFront(middle + new_root_middle, size - new_root_middle, front, 27);
            if(new_left_front > 0)
                recoverLeft(1, front + new_left_front, middle, new_root_middle - 1);
            if(new_right_front > 0)
                recoverRight(1, front + new_right_front, middle + new_root_middle, size - new_root_middle);
        }

        void print()
        {
            if(data[0] == 0)
                cout << "NULL";
            else
                cout << data[0];

            int max_size;
            for(int i=0; i<1002; ++i)
            {
                if(data[i] != 0)
                    max_size = i+1;
            }
            for(int i=1; i<max_size; ++i)
            {
                if(data[i] == 0)
                    cout << " NULL";
                else
                    cout << " " <<data[i];
            }
            cout << endl;
        }

};

int main(void)
{
    Tree tree;
    tree.init();
    tree.getData();
    tree.recover();
    tree.print();
    return 0;
}
