#include <iostream>
using namespace std;

bool compareChar(const char ch1[], const char ch2[], int size)
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
    char origin_text[100] = {0};
    char coded_text[100] = {0};
    char try_text[100] = {0};
    cin >> origin_text;
    cin >> coded_text;
    int text_length = 0;
    do
        ++text_length;
    while(origin_text[text_length]!=0);
    for(int a=2; a <= text_length/2; ++a)
    {
        if(text_length % a != 0)
            continue;
        for(int i=0; i<a; ++i)
        {
            for(int j=0; j< text_length/a; ++j)
                try_text[i * text_length/a + j] = origin_text[i + a * j];
        }
        //cout << try_text << endl;
        if(compareChar(try_text, coded_text, text_length))
        {
            cout << a <<endl;
            return 0;
        }
    }
    cout << "No Solution" << endl;
    return 0;
}
