#include <iostream>
using namespace std;

template<class T >
class BinarySearchTree {
    private:
        struct BinaryNode {
            T data;
            BinaryNode * left, * right;
            int height;
            BinaryNode(const T & d, BinaryNode * l, BinaryNode * r):
                data(d), left(l), right(r), height(1){}
        };
        BinaryNode * root;
        void insert(const T & x, BinaryNode * & t) {
            if (t == NULL)
                t = new BinaryNode(x, NULL, NULL);
            else if (x > t->data) {
                insert(x, t->left);
                if(getHeight(t->left) - getHeight(t->right) == 2) {
                    if(x > t->left->data)
                        LL(t);
                    else
                        LR(t);
                }
                t->height = getHeight(t->left) + getHeight(t->right) + 1;
            } else {
                insert(x, t->right);
                if(getHeight(t->right) - getHeight(t->left) == 2) {
                    if(x <= t->right->data)
                        RR(t);
                    else
                        RL(t);
                }
                t->height = getHeight(t->left) + getHeight(t->right) + 1;
            }
        }
        void remove(const T & x, BinaryNode * & t) {
            if (t == NULL)
                return;
            if (x > t->data) {
                remove(x, t->left);
                if (getHeight(t->right) - getHeight(t->left) == 2) {
                    BinaryNode * r = t->right;
                    if (getHeight(r->left) > getHeight(r->right))
                        RL(t);
                    else
                        RR(t);
                }
                t->height = getHeight(t->left) + getHeight(t->right) + 1;
            } else if (x < t->data) {
                remove(x, t->right);
                if (getHeight(t->left) - getHeight(t->right) == 2) {
                    BinaryNode * r = t->left;
                    if (getHeight(r->right) > getHeight(r->left))
                        LR(t);
                    else
                        LL(t);
                }
                t->height = getHeight(t->left) + getHeight(t->right) + 1;
            } else if (t->left != NULL && t->right != NULL) {
                if (getHeight(t->left) <= getHeight(t->right)) {
                    BinaryNode * tmp = t->right;
                    while (tmp->left != NULL)
                        tmp = tmp->left;
                    t->data = tmp->data;
                    remove(t->data, t->right);
                    t->height = getHeight(t->left) + getHeight(t->right) + 1;
                } else {
                    BinaryNode * tmp = t->left;
                    while (tmp->right != NULL)
                        tmp = tmp->right;
                    t->data = tmp->data;
                    remove(t->data, t->left);
                    t->height = getHeight(t->left) + getHeight(t->right) + 1;
                }
            } else {
                BinaryNode * old = t;
                t = (t->left != NULL) ? t->left : t->right;
                delete old;
            }
        }
        bool find(const T & x, BinaryNode * t) const {
            if (t == NULL)
                return false;
            if (x > t->data)
                return find(x, t->left);
            if (x < t->data)
                return find(x, t->right);
            return true;
        }
        void makeEmpty(BinaryNode * & t) {
            if (t == NULL)
                return;
            BinaryNode * tmp = t;
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete tmp;
            t = NULL;
        }
        T & findith(int i, BinaryNode * & t) {
            int remain = getHeight(t->left);
            if (remain == i - 1) {
                return t->data;
            }
            if (remain >= i)
                return findith(i, t->left);
            else
                return findith(i - remain - 1, t->right);
        }
        int getHeight(BinaryNode * t) {
            return t == NULL ? 0 : t->height;
        }
        void LL(BinaryNode * & t) {
            BinaryNode * t1 = t->left;
            t->left = t1->right;
            t1->right = t;
            t->height = getHeight(t->left) + getHeight(t->right) + 1;
            t1->height = getHeight(t1->left) + getHeight(t) + 1;
            t = t1;
        }
        void RR(BinaryNode * & t) {
            BinaryNode * t1 = t->right;
            t->right = t1->left;
            t1->left = t;
            t->height = getHeight(t->left) + getHeight(t->right) + 1;
            t1->height = getHeight(t1->right) + getHeight(t) + 1;
            t = t1;
        }
        void LR(BinaryNode * & t) {
            RR(t->left);
            LL(t);
        }
        void RL(BinaryNode * & t) {
            LL(t->right);
            RR(t);
        }
    public:
        BinarySearchTree(BinaryNode * t = NULL) {
            root = t;
        }
        ~BinarySearchTree() {
            makeEmpty(root);
        }
        bool find(const T & x) const {
            return find(x, root);
        }
        void insert(const T & x) {
            insert(x, root);
        }
        void remove(const T & x) {
            remove(x, root);
        }
        T & findith(int i) {
            return findith(i, root);
        }
};

int sweet[500005];
int box[500005];
int mergebox[500005] = {0};
int M, N;

int main(void)
{
    cin >> N >> M;
    BinarySearchTree<int> tree;
    for (int i = 1; i <= N; ++i) {
        sweet[i] = i;
        box[i] = 1;
        tree.insert(1);
    }
    char cmd;
    int num1, num2;
    int box_size = N;
    while (M--) {
        cin >> cmd;
        switch(cmd) {
            case 'C':
                cin >> num1 >> num2;
                while (mergebox[sweet[num1]] != 0) {
                    sweet[num1] = mergebox[sweet[num1]];
                }
                while (mergebox[sweet[num2]] != 0) {
                    sweet[num2] = mergebox[sweet[num2]];
                }
                if(sweet[num1] != sweet[num2]
                        && box[sweet[num1]] != 0
                        && box[sweet[num2]] != 0) {
                    tree.remove(box[sweet[num1]]);
                    tree.remove(box[sweet[num2]]);
                    box[sweet[num1]] += box[sweet[num2]];
                    tree.insert(box[sweet[num1]]);
                    box[sweet[num2]] = 0;
                    mergebox[sweet[num2]] = sweet[num1];
                    --box_size;
                }
                break;
            case 'D':
                cin >> num1;
                while (mergebox[sweet[num1]] != 0) {
                    sweet[num1] = mergebox[sweet[num1]];
                }
                if (box[sweet[num1]] != 0) {
                    tree.remove(box[sweet[num1]]);
                    box[sweet[num1]] = 0;
                    --box_size;
                }
                break;
            case 'Q':
                cin >> num1;
                if(box_size < num1)
                    cout << "0" << endl;
                else
                    cout << tree.findith(num1) << endl;
                break;
            default :
                cout << "Wrong" << endl;
                break;
        }
    }
    return 0;
}
