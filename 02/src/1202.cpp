#include <iostream>
using namespace std;

struct node
{
    char data;
    node* next;
};

void addNode(node* p)
{
    node *q;
    q = new node;
    p->next = q;
    q->next = NULL;
}

int main(void)
{
    char ch;
    //node *head1 = new node;
    node *top_p1, *top_p2, *result_head;
    node *p;
    top_p1 = new node;
    top_p2 = new node;
    result_head = new node;
    top_p1->next = NULL;
    top_p2->next = NULL;
    result_head->next = NULL;
    bool isCarry=false;
    char ch1, ch2;
    do
    {
        ch = cin.get();
        p = new node;
        p->data = ch;
        p->next = top_p1;
        top_p1 = p;
    } while(ch!=10);
    do
    {
        ch = cin.get();
        p = new node;
        p->data = ch;
        p->next = top_p2;
        top_p2 = p;
    } while(ch!=10);

    while(top_p1->next!=NULL||top_p2->next!=NULL||isCarry)
    {
        if(top_p1->next != NULL)
            ch1 = top_p1->data; 
        else
            ch1 = '0';
        if(top_p2->next != NULL)
            ch2 = top_p2->data; 
        else
            ch2 = '0';
        ch = ch1 - '0' + ch2 - '0' + isCarry;
        if(ch > 9)
        {
            isCarry = true;
            ch = ch - 10 +'0';
        }
        else
        {
            isCarry = false;
            ch = ch + '0';
        }
        p = new node;
        p->data = ch;
        p->next = NULL;
        p->next = result_head;
        result_head = p;

        if(top_p1->next != NULL)
        {
            p = top_p1->next;
            delete top_p1;
            top_p1 = p;
        }

        if(top_p2->next != NULL)
        {
            p = top_p2->next;
            delete top_p2;
            top_p2 = p;
        }

    }
    delete top_p1;
    delete top_p2;

    while(result_head->next->next!=NULL)
    {
        cout << result_head->data;
        p = result_head->next;
        delete result_head;
        result_head = p;
    }
    cout << endl;
    delete result_head;

    return 0;
}
