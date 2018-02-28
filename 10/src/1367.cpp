#include <iostream>
using namespace std;

class DicTree
{
    private:
        struct Node
        {
            Node * left, * right;//left->0, right->1
            Node():left(NULL), right(NULL){}
        };
        Node * root;
        unsigned long decode_32[32];
    public:
        DicTree()
        {
            root = new Node;
            for(int i=0; i<31; ++i)
            {
                decode_32[i] = 1 << i;
                //cout << i << " " <<  decode_32[i] << endl;
            }
                decode_32[31] = 2147483648;
        }
        void addNumber(unsigned long & num)
        {
            Node * tmp = root;
            for(int i=31; i >= 0; --i)
            {
                if(num & decode_32[i])
                {
                    if(tmp->right == NULL)
                        tmp->right = new Node;
                    tmp = tmp->right;
                }
                else
                {
                    if(tmp->left == NULL)
                        tmp->left = new Node;
                    tmp = tmp->left;
                }
            }
        }
        unsigned long findMax(unsigned long & num)
        {
            unsigned long max = 0;
            Node * tmp = root;
            for(int i=31; i >= 0; --i)
            {
                if(num & decode_32[i])
                {
                    if(tmp->left)
                    {
                        max |= decode_32[i];
                        tmp = tmp->left;
                    }
                    else
                    {
                        tmp = tmp->right;
                    }
                }
                else
                {
                    if(tmp->right)
                    {
                        max |= decode_32[i];
                        tmp = tmp->right;
                    }
                    else
                    {
                        tmp = tmp->left;
                    }
                }
            }
            return max;
        }
};

int main(void)
{
    DicTree dictree;
    unsigned long M, N;
    cin >> N >> M;
    unsigned long a, b;
    unsigned long max = 0;
    unsigned long tmp;
    for(unsigned long i=0; i<N; ++i)
    {
        cin >> a;
        dictree.addNumber(a);
    }
    for(unsigned long i=0; i<M; ++i)
    {
        cin >> b;
        //cout << dictree.findMax(b) << endl;
        tmp = dictree.findMax(b);
        if(tmp > max)
            max = tmp;
    }
    cout << max << endl;
    return 0;
}
