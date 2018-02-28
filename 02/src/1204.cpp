#include <iostream>
#define MAX_ROW 10+1
#define MAX_COL 10+1
#define MAX_STR 9+1
using namespace std;

int MAX(int x1, int x2)
{
        return x1>x2?x1:x2;
}

class Editor
{
    private:
        char text[MAX_ROW][MAX_COL];
        int row;
        int col[MAX_ROW];
        char command[5];
        char command_quit[5];
        char command_list[5];
        char command_ins[5];
        char command_del[5];
        enum STATE{
            INIT,
            QUIT} state;

    public:
        Editor();
        void getTxt();
        void quit();
        void list();
        void ins();
        void del();
        void getCommand();
        bool isQuit();
        bool compareChar(const char ch1[], const char ch2[], int size);
};

Editor::Editor():
    row(0),
    state(INIT)
{
    for(int i=0; i<MAX_ROW; ++i)
        for(int j=0; j<MAX_COL; ++j)
            text[i][j] = 0;
    for(int i=0; i<MAX_ROW; ++i)
        col[i] = 0;
    for(int i=0; i<5; ++i)
        command[i] = 0;

    char quit[5] = "quit";
    for(int i=0; i<5; ++i)
        command_quit[i] = quit[i];

    char list[5] = "list";
    for(int i=0; i<5; ++i)
        command_list[i] = list[i];
    char ins[5] = "ins";
    for(int i=0; i<5; ++i)
        command_ins[i] = ins[i];
    char del[5] = "del";
    for(int i=0; i<5; ++i)
        command_del[i] = del[i];

}

void Editor::getTxt()
{
    char end_of_file[7] = "******";
    char ch;
    end_of_file[6] = 0;
    for(int i=0; i<MAX_ROW; ++i)
    {
        for(int j=0; j<MAX_COL; ++j)
        {
            ch = cin.get();
            if(ch == 10)
            {
               text[i][j] = 0;
                break;
            }
            text[i][j] = ch;
        }
        //cin.getline(text[i], MAX_COL);
        for(int j=0; j<MAX_COL; ++j)
        {
            if(text[i][j] == 0)
            {
                col[i] = j;
                break;
            }
        }
        if(compareChar(text[i], end_of_file, 7)
                &&text[i][6] == 0)
        {
            row = i;
            break;
        }
    }
}

void Editor::quit()
{
    state = QUIT;
    char end_of_file[7] = "******";
    end_of_file[6] = 0;
    for(int i=0; i<MAX_ROW; ++i)
    {
        if(compareChar(text[i], end_of_file, 7)
                &&text[i][6] == 0)
            break;
        cout << text[i] << endl;
    }
}

void Editor::list()
{
    long n1, n2;
    cin >> n1 >> n2;
    if(n1<1||n2<1
            ||n1>row||n2>row||n1>n2)
    {
        cout << "Error!"<<endl;
        return;
    }
    for(int i=n1-1; i<n2; ++i)
        cout << text[i] <<endl;
}

void Editor::ins()
{
    long ins_row, ins_col, str_length = 0;
    char str[MAX_STR] = {0};
    cin >> ins_row >> ins_col;
    cin.get();
    cin.getline(str, MAX_STR);
    for(int i=0; i<MAX_STR; ++i)
    {
        if(str[i] == 0)
            break;
        ++str_length;
    }

    if(ins_row<=0
            ||ins_col<=0
            //||text[ins_row-1][MAX(ins_col-2,0)] == 0
            ||ins_col > col[ins_row - 1] + 1
            //||ins_col + str_length > MAX_COL - 1
            ||col[ins_row-1] + str_length > MAX_COL - 1
            ||ins_row > row)
    {
        cout << "Error!" << endl;
        return;
    }
    
    for(int i=MAX_COL-str_length; i>ins_col-1; --i)
    {
        //if(text[ins_row - 1][i + str_length - 1] == 0)
            //continue;
        text[ins_row - 1][i + str_length -1] = text[ins_row - 1][i - 1];
    }
    for(int i=0; i<str_length; ++i)
    {
        text[ins_row-1][ins_col + i - 1] = str[i];
    }
    col[ins_row - 1]+=str_length;
}

void Editor::del()
{
    long del_row, del_col, del_length;
    cin >> del_row >> del_col >> del_length;
    if(del_row<=0
            ||del_col<=0
            ||del_length<=0
            ||del_col + del_length - 1 > col[del_row - 1]
            ||(del_col == 1 && del_length == col[del_row - 1])
            //||text[del_row-1][del_col-1] == 0
            //||text[del_row-1][del_col+del_length-2] == 0
            ||del_row > row)
    {
        cout << "Error!" << endl;
        return;
    }

    for(int i=0; i<col[del_row-1]-del_length-del_col+2; ++i)
    {
        text[del_row - 1][del_col + i - 1] = text[del_row - 1][del_col + i + del_length - 1];
        //if(text[del_row - 1][del_col + i - 1] == 0)
            //break;
    }
    col[del_row - 1] -= del_length;
}

void Editor::getCommand()
{
    cin >> command;
    if(compareChar(command, command_quit, 5))
    {
        quit();
        //while(cin.get()!=10);
        return;
    }
    if(compareChar(command, command_list, 5))
    {
        list();
        //while(cin.get()!=10);
        return;
    }
    if(compareChar(command, command_ins, 5))
    {
        ins();
        return;
    }
    if(compareChar(command, command_del, 5))
    {
        del();
        //while(cin.get()!=10);
        return;
    }
    cout << "Error!" << endl;
    //while(cin.get()!=10);
}

bool Editor::isQuit()
{
    return state == QUIT;
}

bool Editor::compareChar(const char ch1[], const char ch2[], int size)
{
    for(int i=0;i<size;i++)
    {
        if(ch1[i]==0||ch2[i]==0)
        {
            if(ch1[i]==0&&ch2[i]==0)
            {
                break;
            }
            else
            {
                return false;
            }
        }
        if(ch1[i]!=ch2[i])
            return false;
    }
    return true;
}

int main(void)
{

    Editor editor;
    editor.getTxt();
    while(!editor.isQuit())
    {
        editor.getCommand();
    }
    return 0;
}
