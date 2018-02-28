#include <iostream>
using namespace std;
#include <stdlib.h>
#include <iomanip>
//#define DEBUG

//typedef unsigned long long;
typedef unsigned int uint;

template <class T>
class AVLTreeNode{
    public:
        T key;               
        long height;         
        AVLTreeNode *left; 
        AVLTreeNode *right;

        AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r):
            key(value), height(0),left(l),right(r) {}
};

template <class T>
class AVLTree {
    private:
        AVLTreeNode<T> *mRoot; 

    public:
        AVLTree();
        ~AVLTree();

        long height();
        long max(long a, long b);

        AVLTreeNode<T>* search(T key);
        AVLTreeNode<T>* iterativeSearch(T key);

        T minimum();
        T maximum();

        void insert(T key);

        void remove(T key);

        void destroy();

        void print();
    private:
        long height(AVLTreeNode<T>* tree) ;

        AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;
        AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;

        AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
        AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

        AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);

        AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);

        AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);

        AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);

        AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);

        AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);

        void destroy(AVLTreeNode<T>* &tree);

        void print(AVLTreeNode<T>* tree, T key, int direction);
};

template <class T>
AVLTree<T>::AVLTree():mRoot(NULL)
{
}

template <class T>
AVLTree<T>::~AVLTree() 
{
    destroy(mRoot);
}

template <class T>
long AVLTree<T>::height(AVLTreeNode<T>* tree) 
{
    if (tree != NULL)
        return tree->height;

    return 0;
}

template <class T>
long AVLTree<T>::height() 
{
    return height(mRoot);
}
template <class T>
long AVLTree<T>::max(long a, long b) 
{
    return a>b ? a : b;
}
template <class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* x, T key) const
{
    if (x==NULL || x->key==key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::search(T key) 
{
    return search(mRoot, key);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* x, T key) const
{
    while ((x!=NULL) && (x->key!=key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(mRoot, key);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <class T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T> *p = minimum(mRoot);
    if (p != NULL)
        return p->key;

    return T();
}
 
template <class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
    AVLTreeNode<T>* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height(k2->left), height(k2->right)) + 1;
    k1->height = max( height(k1->left), k2->height) + 1;

    return k1;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
    AVLTreeNode<T>* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height(k1->left), height(k1->right)) + 1;
    k2->height = max( height(k2->right), k1->height) + 1;

    return k2;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{
    if (tree == NULL) 
    {
        tree = new AVLTreeNode<T>(key, NULL, NULL);
    }
    else if (key < tree->key) 
    {
        tree->left = insert(tree->left, key);
        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else if (key > tree->key) 
    {
        tree->right = insert(tree->right, key);
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }

    tree->height = max( height(tree->left), height(tree->right)) + 1;

    return tree;
}

template <class T>
void AVLTree<T>::insert(T key)
{
    insert(mRoot, key);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z)
{
    if (tree==NULL || z==NULL)
        return NULL;

    if (z->key < tree->key)        
    {
        tree->left = remove(tree->left, z);
        if (height(tree->right) - height(tree->left) == 2)
        {
            AVLTreeNode<T> *r =  tree->right;
            if (height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key)
    {
        tree->right = remove(tree->right, z);
        if (height(tree->left) - height(tree->right) == 2)
        {
            AVLTreeNode<T> *l =  tree->left;
            if (height(l->right) > height(l->left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else
    {
        if ((tree->left!=NULL) && (tree->right!=NULL))
        {
            if (height(tree->left) > height(tree->right))
            {
                AVLTreeNode<T>* max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                AVLTreeNode<T>* min = maximum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode<T>* tmp = tree;
            tree = (tree->left!=NULL) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

template <class T>
void AVLTree<T>::remove(T key)
{
    AVLTreeNode<T>* z; 

    if ((z = search(mRoot, key)) != NULL)
        mRoot = remove(mRoot, z);
}

template <class T>
void AVLTree<T>::destroy(AVLTreeNode<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        destroy(tree->left);
    if (tree->right != NULL)
        destroy(tree->right);

    delete tree;
}

template <class T>
void AVLTree<T>::destroy()
{
    destroy(mRoot);
}


template< class TypeOfVer, class TypeOfEdge >
class adjListGraph
{
    private:
        long Vers, Edges;

    public:
        adjListGraph(long vSize) {
            Vers = vSize;
            Edges = 0;

            verList = new verNode[vSize];
            for (long i = 0; i < Vers; ++i) {
                verList[i].ver = i;
            }
        }
        bool insert(long u, long v, TypeOfEdge w) {
            verList[u].head = new edgeNode(v, w, verList[u].head);
            ++Edges;
            return true;
        }
        bool remove(long u, long v) {
            edgeNode * p = verList[u].head, * q;
            if (p == NULL)
                return false;
            if (p->end == v) {
                verList[u].head = p->next;
                delete p;
                --Edges;
                return true;
            }
            while (p->next != NULL && p->next->end != v) {
                p = p->next;
            }
            if (p->next == NULL) {
                return false;
            }
            q = p->next;
            p->next = q->next;
            delete q;
            --Edges;
            return true;
        }
        bool exist(long u, long v) const {
            edgeNode * p = verList[u].head;

            while (p != NULL && p->next != v) {
                p = p->next;
            }
            if (p == NULL) 
                return false;
            else
                return true;
        }
        ~adjListGraph() {
            edgeNode * p;
            for (long i = 0; i < Vers; ++i) {
                while ((p = verList[i].head) != NULL) {
                    verList[i].head = p->next;
                    delete p;
                }
            }
            delete [] verList;
        }
        void search(TypeOfEdge noEdge, TypeOfVer end) const {
            bool * flag = new bool [Vers];
            costNode * lowCost = new costNode[Vers];
            //long * startNode = new long [Vers];

            edgeNode * p;
            long i, tmp;
            costNode min_node;
            
            AVLTree< costNode > tree;

            for (long i = 1; i < Vers; ++i) {
                flag[i] = false;
                lowCost[i].cost = noEdge;
                lowCost[i].ver = i;
                tree.insert(lowCost[i]);
            }
            lowCost[0].cost = 0;
            lowCost[0].ver = 0;
            flag[0] = true;
            min_node = lowCost[0];
            for (long i = 0; i < Edges; ++i) {
                flag[min_node.ver] = true;
                for (p = verList[min_node.ver].head; p != NULL; p = p->next) {
                    if(flag[p->end])
                        continue;
                    tmp = p->weight + min_node.cost;
                    if (tmp < lowCost[p->end].cost) {
                        tree.remove(lowCost[p->end]);
                        lowCost[p->end].cost = tmp;
                        tree.insert(lowCost[p->end]);
                    }
                }
                min_node = tree.minimum();
                if (min_node.ver == end)
                    break;
                tree.remove(min_node);
            }

            cout << lowCost[end].cost << endl;

            delete [] flag;
            //delete [] startNode;
            delete [] lowCost;
        }

    private:
        struct edgeNode {
            long end;
            TypeOfEdge weight;
            edgeNode * next;

            edgeNode (long e, TypeOfEdge w, edgeNode * n = NULL):
                end(e), weight(w), next(n) {}
        };

        struct verNode {
            TypeOfVer ver;
            edgeNode * head;

            verNode (edgeNode * h = NULL): head(h){}
        };

        struct costNode {
            TypeOfEdge cost;
            long ver;
            bool operator == (costNode & c2) {
                return cost == c2.cost && ver == c2.ver;
            }
            bool operator < (costNode & c2) {
                if (cost == c2.cost)
                    return ver < c2.ver;
                return cost < c2.cost;
            }
            bool operator > (costNode & c2) {
                if (cost == c2.cost)
                    return ver > c2.ver;
                return cost > c2.cost;
            }
            bool operator <= (costNode & c2) {
                if (cost < c2.cost)
                    return true;
                if (cost == c2.cost)
                    return ver <= c2.ver;
            }
            bool operator >= (costNode & c2) {
                if (cost > c2.cost)
                    return true;
                if (cost == c2.cost)
                    return ver >= c2.ver;
            }
        };

        verNode * verList;
};

//int main(void)
//{
    //long N;
    //long tmp;
    //cin >> N;
    //AVLTree<long> tree;
    //for (long i=0; i<N; ++i) {
        //tmp = rand() % 10000;
        //tree.insert(tmp);
    //}
    //for (long i=0; i<N; ++i) {
        //tmp = rand() % 10000;
        //tree.remove(tmp);
    //}
    //return 0;
//}

int main(void)
{
    long N, M;
    cin >> N >> M;
    adjListGraph<long, long>  route(N);
    long v_start, v_end;
    int transport;
    for (long i = 0; i < M; ++i) {
#ifdef DEBUG
        v_start = rand() % N + 1;
        v_end = rand() % N + 1;
        transport = rand() % 3 + 1;
        cout << v_start << "\t" << v_end << "\t" << transport << endl;
#else
        cin >> v_start >> v_end >> transport;
#endif
        route.insert(v_start-1, v_end-1, transport);
        route.insert(v_end-1, v_start-1, transport);
    }
    route.search(5000005, N-1);
    return 0;
}

