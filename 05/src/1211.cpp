#include <iostream>
using namespace std;

struct Node
{
    Node *left_child = NULL, *right_child = NULL;
};

class Tree
{
    private:
        long node_size;
        Node *nodes;
        Node *root;
        bool *isRoot;
        bool isOutSize;
        //long *tree_array;

        void getRoot()
        {
            for(long i=1; i<=node_size; ++i)
            {
                if(isRoot[i])
                {
                    root = &nodes[i];
                    //tree_array[1] = i;
                    return;
                }
            }
        }

        void getArray(long root_position, Node* root)
        {
            if(root->left_child != NULL)
            {
                if(2*root_position > node_size)
                {
                    isOutSize = true;
                    return;
                }
                //tree_array[2*root_position] = root->left_child - nodes;
                getArray(2*root_position, root->left_child);
            }
            if(root->right_child != NULL)
            {
                //tree_array[2*root_position+1] = root->right_child - nodes;
                if(2*root_position + 1 > node_size)
                {
                    isOutSize = true;
                    return;
                }
                getArray(2*root_position+1, root->right_child);
            }
        }

    public:
        Tree():nodes(NULL),isOutSize(false){}
        ~Tree()
        {
            if(nodes != NULL)
                delete[] nodes;
        }
        
        void create(long node_number)
        {
            node_size = node_number;
            nodes = new Node[node_number + 1];
            isRoot = new bool[node_number + 1];
            //tree_array = new long[node_number + 1];
            isRoot[0] = false;
            for(long i=1; i<=node_size; ++i)
            {
                isRoot[i] = true;
                //tree_array[i] = 0;
            }
        }

        void addNode(long number)
        {
            long left_child, right_child;
            cin >> left_child >> right_child;
            if(left_child > 0)
            {
                nodes[number].left_child = &nodes[left_child];
                isRoot[left_child] = false;
            } 
            if(right_child > 0)
            {
                nodes[number].right_child = &nodes[right_child];
                isRoot[right_child] = false;
            }
        }

        bool isCBT()
        {
            getRoot();
            getArray(1, root);
            return !isOutSize;
        }

};

int main(void)
{
    Tree tree;
    long node_num = 0;
    cin >> node_num;
    tree.create(node_num);
    for(long i=1; i<=node_num; ++i)
    {
        tree.addNode(i);
    }
    if(tree.isCBT())
        cout << "Y" << endl;
    else
        cout << "N" << endl;
    return 0;
}
