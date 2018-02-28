#include <iostream>
using namespace std;

class CharTree
{
    private:
        char *tree;
        unsigned long size;
        char **decode_char;
        unsigned long decode_position;
        enum {
            ENCODE,
            DECODE
        }   code_cmd;
        enum {
            INORDER,
            PREORDER,
            POSTORDER
        }   order_cmd;
        unsigned long depth;
        unsigned long bottom_layer_cnt;

        bool compareChar(char ch1[], char ch2[], int size)
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

        void getDepth()
        {
            unsigned long tmp = 1;
            depth = 0;
            while(tmp<=size)
            {
                ++depth;
                tmp*=2;
            }
            bottom_layer_cnt = size - tmp/2 + 1;
        }

        void inorderEncode(unsigned long root)
        {
            if(root > size)
                return;
            inorderEncode(root*2);
            cout << tree[root];
            inorderEncode(root*2 + 1);
        }

        void preorderEncode(unsigned long root)
        {
            if(root > size)
                return;
            cout << tree[root];
            preorderEncode(root*2);
            preorderEncode(root*2 + 1);
        }

        void postorderEncode(unsigned long root)
        {
            if(root > size)
                return;
            postorderEncode(root*2);
            postorderEncode(root*2 + 1);
            cout << tree[root];
        }


        void encode()
        {
            switch(order_cmd)
            {
                case INORDER: inorderEncode(1); break;
                case PREORDER: preorderEncode(1); break;
                case POSTORDER: postorderEncode(1); break; 
                default: break;
            }
            cout << endl;
        }

        void inorderDecode(unsigned long root)
        {
            if(root>size)
                return;
            inorderDecode(root*2);
            decode_char[root] = &tree[decode_position];
            ++decode_position;
            inorderDecode(root*2+1);

        }

        void preorderDecode(unsigned long root)
        {
            if(root>size)
                return;
            decode_char[root] = &tree[decode_position];
            ++decode_position;
            preorderDecode(root*2);
            preorderDecode(root*2+1);
        }

        void postorderDecode(unsigned long root)
        {
            if(root>size)
                return;
            postorderDecode(root*2);
            postorderDecode(root*2+1);
            decode_char[root] = &tree[decode_position];
            ++decode_position;

        }

        void decode()
        {
            decode_char = new char* [size+1];
            decode_position = 1;
            switch(order_cmd)
            {
                case INORDER: inorderDecode(1); break;
                case PREORDER: preorderDecode(1); break;
                case POSTORDER: postorderDecode(1); break;
                default: break;
            }
            for(unsigned long i=1; i<=size; ++i)
                cout << *decode_char[i];
            cout << endl;
        }

    public:
        CharTree():tree(NULL), size(0),decode_char(NULL){}
        ~CharTree()
        {
            if(tree!=NULL)
                delete [] tree;
        }

        void create()
        {
            cin >> size;
            tree = new char [size + 1];
            getCommand();
            input();
            getDepth();
        }

        void getCommand()
        {
            char tmp1[10], tmp2[7];
            cin >> tmp1;
            cin >> tmp2;

            char ch_encode[7] = "ENCODE", ch_decode[7] = "DECODE";
            char ch_inorder[10] = "INORDER", ch_preorder[10] = "PREORDER", ch_postorder[10] = "POSTORDER";

            if(compareChar(tmp1, ch_inorder, 10))
                order_cmd = INORDER;
            if(compareChar(tmp1, ch_preorder, 10))
                order_cmd = PREORDER;
            if(compareChar(tmp1, ch_postorder, 10))
                order_cmd = POSTORDER;
            if(compareChar(tmp2, ch_encode, 7))
                code_cmd = ENCODE;
            if(compareChar(tmp2, ch_decode, 7))
                code_cmd = DECODE;

        }

        void input()
        {
            cin >> (tree+1);
        }

        void print()
        {
            /*
            cout << "Order: " << order_cmd << endl;
            cout << "Code: " << code_cmd << endl;
            cout << "string: " << tree+1 << endl;
            cout << "depth: " << depth << endl;
            cout << "buttom layer: " << bottom_layer_cnt << endl;
            */
            switch(code_cmd)
            {
                case ENCODE: encode(); break;
                case DECODE: decode(); break;
                default: break;
            }
        }
};

int main(void)
{
    int tree_cnt = 0;
    cin >> tree_cnt;

    CharTree *char_tree = new CharTree [tree_cnt];
    for(int i=0; i<tree_cnt; ++i)
        char_tree[i].create();
    for(int i=0; i<tree_cnt; ++i)
        char_tree[i].print();
    return 0;
}
