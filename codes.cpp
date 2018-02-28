#include <iostream>
#include <vector>
using namespace std;

template < class elemType >
class list
{
    public:
        virtual void clear() = 0;
        virtual int length() const = 0;
        virtual void insert(int i, const elemType & x) = 0;
        virtual void remove(int i) = 0;
        virtual int search(const elemType & x) const = 0;
        virtual elemType visit(int i) const = 0;
        virtual void traverse() const = 0;
        virtual ~list() {};
};

class OutOfBound{};
class IllegalSize{};

template < class elemType >
class seqList: public list < elemType >
{
    private:
        elemType * data;
        int currentLength;
        int maxSize;

        void doubleSpace();
    public:
        seqList(int initSize = 10);
        ~seqList() {delete [] data;}
        void clear() {currentLength = 0;};
        int length() const {return currentLength;};
        void insert(int i, const elemType & x);
        void remove(int i);
        int search(const elemType & x) const;
        elemType visit(int i) const;
        void traverse() const;
};

template < class elemType >
void seqList < elemType > :: doubleSpace() {
    elemType * tmp = data;
    maxSize *= 2;
    data = new elemType [maxSize];
    for (int i = 0; i < currentLength; ++i)
        data[i] = tmp[i];
    delete [] tmp;
}

template < class elemType >
seqList < elemType > :: seqList(int initSize) {
    if (initSize <= 0)
        throw IllegalSize();
    data = new elemType [initSize];
    maxSize = initSize;
    currentLength = 0;
}

template < class elemType >
void seqList < elemType > :: insert(int i, const elemType & x) {
    if (i < 0 || i > currentLength)
        throw OutOfBound();
    if (currentLength == maxSize)
        doubleSpace();
    for ( int j = currentLength; j > i; j--) {
        data[j] = data[j - 1];
    }
    data[i] = x;
    ++currentLength;
}

template < class elemType >
void seqList < elemType > :: remove(int i) {
    if (i < 0 || i > currentLength - 1)
        throw OutOfBound();
    for (int j = i; j < currentLength - 1; j++) {
        data[j] = data[j + 1];
    }
    --currentLength;
}

template < class elemType >
int seqList < elemType > :: search(const elemType & x) const {
    for (int i = 0; i < currentLength && data[i] != x; ++i)
        if(i == currentLength)
            return -1;
        else
            return i;
}

template < class elemType >
elemType seqList < elemType > :: visit(int i) const {
    if (i < 0 || i > currentLength - 1)
        throw OutOfBound();
    return data[i];
}

template < class elemType >
void seqList < elemType > :: traverse() const {
    cout << endl;
    for (int i = 0; i < currentLength; ++i)
        cout << data[i] << ' ';
}

template < class elemType >
class linkList: public list< elemType >
{
    private:
        struct node
        {
            elemType data;
            node * prev, * next;

            node(const elemType & x, node * p = NULL, node * n = NULL) {
                data = x;
                next = n;
                prev = p;
            }
            node() : next(NULL), prev(NULL) {}
            ~node() {}
        };

        node * head, * tail;
        int currentLength;

        node * move(int i) const;

    public:
        linkList();
        ~linkList() {clear(); delete head; delete tail;}

        void clear();
        int lenght() const {return currentLength;}
        void insert(int i, const elemType & x);
        void remove(int i);
        int search(const elemType & x) const;
        elemType visit(int i) const;
        void traverse() const;
};

template < class elemType >
typename linkList < elemType > ::node * linkList < elemType > :: move(int i) const {
    node * p = head->next;
    if (i < 0 || i > currentLength)
        throw OutOfBound();
    while(i--)
        p = p->next;
    return p;
}

template < class elemType >
linkList < elemType > :: linkList() {
    head = new node;
    head->next = tail = new node;
    tail->prev = head;
    currentLength = 0;
}

template < class elemType >
void linkList < elemType > :: clear() {
    node * p = head->next, *q;
    head -> next = tail;
    tail -> prev = head;
    while(p != tail) {
        q = p -> next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

template < class elemType >
void linkList < elemType > :: insert(int i, const elemType & x) {
    node * pos, * tmp;
    
    pos = move(i);
    tmp = new node(x, pos -> prev, pos);
    pos -> prev -> next = tmp;
    pos -> prev = tmp;

    ++currentLength;
}

template < class elemType >
void linkList < elemType > :: remove(int i) {
    node * pos;

    pos = move(i);
    pos -> prev -> next = pos -> next;
    pos -> next -> prev = pos -> prev;

    delete pos;
    --currentLength;
}

template < class elemType >
int linkList < elemType > :: search(const elemType & x) const {
    node * p = head -> next;
    int i = 0;

    while (p != tail && p -> data != x) {
        p = p -> next;
        ++i;
    }
    if (p == tail)
        return -1;
    else
        return i;
}

template < class elemType >
elemType linkList < elemType > :: visit(int i) const {
    node * p = move(i);
    return p -> data;
}

template < class elemType >
void linkList < elemType > :: traverse() const {
    node * p = head -> next;
    cout << endl;
    while (p != tail) {
        cout << p -> data << " ";
        p = p -> next;
    }
    cout << endl;
}

template < class elemType >
class stack
{
    public:
        virtual bool isEmpty() const = 0;
        virtual bool push(const elemType & x) = 0;
        virtual elemType pop() = 0;
        virtual elemType top() const = 0;
        virtual ~stack() {}
};

template < class elemType >
class seqStack: public stack < elemType >
{
    private:
        elemType * elem;
        int top_p;
        int maxSize;

        void doubleSpace();

    public:
        seqStack(int initSize = 10) {
            elem = new elemType[initSize];
            maxSize = initSize;
            top_p = -1;
        }

        ~seqStack() {delete [] elem;}

        bool isEmpty() const {return top_p == -1;}

        void push(const elemType & x) {
            if (top_p == maxSize - 1) doubleSpace();
            elem[++top_p] = x;
        }

        elemType pop() {return elem[top_p --];}

        elemType top() {return elem[top_p];}
};

template < class elemType >
void seqStack < elemType > :: doubleSpace() {
    elemType * tmp = elem;

    elem = new elemType[2*maxSize];

    for (int i = 0; i < maxSize; ++i)
        elem[i] = tmp[i];
    maxSize *= 2;
    delete [] tmp;
}

template < class elemType >
class linkStack: public stack < elemType >
{
    public:
        struct node
        {
            elemType data;
            node * next;
            node(const elemType & x, node * N = NULL) {
                data = x;
                next = N;
            }
            node() : next(NULL) {}
            ~node() {}
        };

        node * elem;

    public:
        linkStack() {elem = NULL;}
        
        ~linkStack();
        
        bool isEmpty() const {return elem == NULL;}

        void push(const elemType & x) {
            node * tmp = new node(x, elem);
            elem = tmp;
        }

        elemType pop() {
            node * tmp = elem;
            elemType x = tmp -> data;
            elem = elem -> next;
            delete tmp;
            return x;
        }

        elemType top() const {return elem -> data;}
};

template < class elemType >
linkStack < elemType > :: ~linkStack() {
    node * tmp;
    while(elem != NULL) {
        tmp = elem;
        elem = elem -> next;
        delete tmp;
    }
}

template < class elemType >
class queue
{
    public:
        virtual bool isEmpty() = 0;
        virtual void enQueue(const elemType & x) = 0;
        virtual elemType deQueue() = 0;
        virtual elemType getHead() = 0;
        virtual ~queue() {}
};

template < class elemType >
class seqQueue: public queue < elemType >
{
    private:
        elemType * elem;
        int maxSize;
        int front, rear;

        void doubleSpace();

    public:
        seqQueue(int size = 10) {
            elem = new elemType[size];
            maxSize = size;
            front = rear = 0;
        }

        ~seqQueue() {delete [] elem;}

        bool isEmpty() {return front == rear;}

        void enQueue(const elemType & x);

        elemType deQueue();

        elemType getHead() {return elem[(front + 1) % maxSize];}
};

template < class elemType >
void seqQueue < elemType > :: doubleSpace() {
    elemType * tmp = elem;

    elem = new elemType[2 * maxSize];

    for (int i = 1; i < maxSize; ++i) {
        elem[i] = tmp[(front + 1) % maxSize];
    }

    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;

    delete tmp;
}

template < class elemType >
void seqQueue < elemType > :: enQueue(const elemType & x) {
    if ((rear + 1) % maxSize == front)
        doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template < class elemType >
elemType seqQueue < elemType > :: deQueue() {
    front = (front + 1) % maxSize;
    return elem[front];
}

template < class elemType >
class linkQueue: public queue < elemType >
{
    private:
        struct node
        {
            elemType data;
            node * next;
            node(const elemType & x, node * N = NULL) {
                data = x;
                next = N;
            }
            node():next(NULL) {}
            ~node() {}
        };
        
        node * front, * rear;

    public:
        linkQueue() {front = rear = NULL;}

        ~linkQueue();

        bool isEmpty() {return front == NULL;}

        void enQueue(const elemType & x);

        elemType deQueue();

        elemType getHead() {return front -> data;}
};

template < class elemType >
linkQueue < elemType > :: ~linkQueue() {
    node * tmp;
    while (front != NULL) {
        tmp = front;
        front = front -> next;
        delete tmp;
    }
}

template < class elemType >
void linkQueue < elemType > :: enQueue(const elemType & x) {
    if (rear == NULL)
        front = rear = new node(x);
    else {
        rear -> next = new node(x);
        rear = rear -> next;
    }
}

template < class elemType >
elemType linkQueue < elemType > :: deQueue() {
    node * tmp = front;
    elemType value = front -> data;
    front = front -> next;
    if (front == NULL)
        rear = NULL;
    delete tmp;
    return value;
}

template < class Type >
class BinaryTree
{
    private:
        struct Node
        {
            Node * left, * right;
            Type data;

            Node(): left(NULL), right(NULL) {}
            Node(Type item, Node * L = NULL, Node * R = NULL)
                :data(item), left(L), right(R) {}
            ~Node() {}
        };

        struct StNode
        {
            Node * node;
            int TimesPop;

            StNode(Node * N = NULL): node(N), TimesPop(0) {}
        };

        Node * root;

    public:
        BinaryTree(): root(NULL) {}
        BinaryTree(const Type & value) {root = new Node(value);}
        BinaryTree(const Node * P) {root = P;}
        ~BinaryTree() {clear();}

        Type getRoot() const {return root -> data;}
        Type getLeft() const {return root -> left -> data;}
        Type getRight() const {return root -> right -> data;}

        void makeTree(const Type & x, BinaryTree & lt, BinaryTree & rt) {
            root = new Node(x, lt.root, rt.root);
            lt.root = NULL;
            rt.root = NULL;
        }

        void delLeft() {
            BinaryTree tmp = root -> left;
            root -> left = NULL;
            tmp.clear();
        }

        void delRight() {
            BinaryTree tmp = root -> right;
            root -> right = NULL;
            tmp.clear();
        }

        bool isEmpty () const {return root == NULL;}

        void clear() {
            if (root != NULL)
                clear(root);
            root = NULL;
        }

        int size() const {return size(root);}

        int height() const {return height(root);}

        void preOrder() const;
        void postOrder() const;
        void midOrder() const;
        //void preOrder() const {
            //if (root != NULL) {
                //cout << "\nPreOrder:";
                //preOrder(root);
            //}
        //}

        //void postOrder() const {
            //if (root != NULL) {
                //cout << "\npostOrder:";
                //postOrder(root);
            //}
        //}

        //void midOrder() const {
            //if (root != NULL) {
                //cout << "\nmidOrder:";
                //midOrder(root);
            //}
        //}

        void createTree(Type flag);

    private:
        int height(Node * t) const {
            if (t == NULL)
                return 0;
            else {
                int lt = height(t -> left), rt = height(t -> right);
                return 1 + ((lt > rt ) ? lt : rt);
            }
        }

        void clear(Node * t) {
            if (t -> left != NULL)
                clear(t -> left);
            if (t -> right != NULL)
                clear(t -> right);
            delete t;
        }

        int size(Node * t) const {
            if (t == NULL)
                return 0;
            return 1 + size(t -> left) + size(t -> right);
        }

        void preOrder(Node * t) const {
            if (t != NULL) {
                cout << t -> data << ' ';
                preOrder(t -> left);
                preOrder(t -> right);
            }
        }

        void postOrder(Node * t) const {
            if (t != NULL) {
                postOrder(t -> left);
                postOrder(t -> right);
                cout << t -> data << ' ';
            }
        }

        void midOrder(Node * t) const {
            if (t != NULL) {
                midOrder(t -> left);
                cout << t -> data << ' ';
                midOrder(t -> right);
            }
        }
};

template < class Type >
void BinaryTree < Type > :: createTree(Type flag) {
    linkQueue < Node * > que;
    Node * tmp;
    Type x, ldata, rdata;

    cout << "\n Input Root:";
    cin >> x;
    root = new Node(x);
    que.enQueue(root);

    while(!que.isEmpty()) {
        tmp = que.deQueue();
        cout << "\n input" << tmp -> data << "childs (" << flag << "means NULL):";
        cin >> ldata >> rdata;
        if (ldata != flag)
            que.enQueue(tmp -> left = new Node(ldata));
        if (rdata != flag)
            que.enQueue(tmp -> right = new Node(rdata));
    }

    cout << "create completed \n";
}

template < class Type >
void BinaryTree < Type > :: preOrder() const {
    linkStack < Node * > s;
    Node * current;

    cout << "preOrder:";
    s.push(root);
    while(! s.isEmpty()) {
        current = s.pop();
        cout << current -> data;
        if (current -> right != NULL)
            s.push(current -> right);
        if (current -> left != NULL)
            s.push(current -> left);
    }
}

template < class Type >
void BinaryTree < Type > :: midOrder() const {
    linkStack < StNode > s;
    StNode current(root);

    cout << "midOrder:";
    s.push(current);
    while (! s.isEmpty()) {
        current = s.pop();
        if (++current.TimesPop == 2) {
            cout << current.node -> data;
            if (current.node -> right != NULL)
                s.push(StNode(current.node -> right));
        } else {
            s.push(current);
            if (current.node -> left != NULL)
                s.push(StNode(current.node -> left));
        }
    }
}


template < class Type >
void BinaryTree < Type > :: postOrder() const {
    linkStack < StNode > s;
    StNode current(root);

    cout << "postOrder:";
    s.push(current);
    while (! s.isEmpty()) {
        current = s.pop();
        if (++current.TimesPop == 3) {
            cout << current.node -> data;
            continue;
        }
        s.push(current);
        if (current.TimesPop == 1) {
            if (current.node -> left != NULL)
                s.push(StNode(current.node -> left));
        } else {
            if (current.node -> right != NULL)
                s.push(StNode(current.node -> right));
        }
    }
}

template < class Type >
class hfTree
{
    private:
        struct Node
        {
            Type data;
            int weight;
            int parent, left, right;
        };

        Node * elem;
        int length;

    public:
        struct hfCode
        {
            Type data;
            string code;
        };

        hfTree(const Type * x, const int * w, int size);
        void getCode(hfCode result[]);
        ~hfTree() {delete [] elem;}
};

template < class Type >
hfTree < Type > :: hfTree(const Type * v, const int * w, int size) {
    const int MAX_INT = 32767;
    int min1, min2;
    int x, y;

    length = 2 * size;
    elem = new Node [length];

    for (int i = size; i < length; ++i){
        elem[i].weight = w[i-size];
        elem[i].data = v[i-size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }
    for (int i = size - 1; i > 0; --i) {
        min1 = min2 = MAX_INT;
        x = y = 0;
        for (int j = i + 1; j < length; ++j) {
            if (elem[j].parent == 0) {
                if (elem[j].weight < min1) {
                    min2 = min1;
                    min1 = elem[j].weight;
                    y = x;
                    x = j;
                } else if (elem[j].weight < min2) {
                    min2 = elem[j].weight;
                    y = j;
                }
            }
        }
        elem[i].weight = min1 + min2;
        elem[i].left = x;
        elem[i].right = y;
        elem[i].parent = 0;
        elem[x].parent = i;
        elem[y].parent = i;
    }
}

template < class Type >
void hfTree < Type > :: getCode(hfCode result[]) {
    int size = length / 2;
    int p, s;
    for (int i = size; i < length; ++i) {
        result[i - size].data = elem[i].data;
        result[i - size].code = " ";
        p = elem[i].parent;
        s = i;
        while (p) {
            if (elem[p].left == s) {
                result[i - size].code = '0' + result[i - size].code;
            } else {
                result[i - size].code = '1' + result[i - size].code;
            }
            s = p;
            p = elem[p].parent;
        }
    }
}

template < class Type >
class priorityQueue
{
public:
    priorityQueue (int capacity = 100) {
        array = new Type [capacity];
        maxSize = capacity;
        currentSize = 0;
    }
    priorityQueue(const Type data[], int size);
    ~priorityQueue () {delete [] array;}

    bool isEmpty() const {return currentSize == 0;}
    void enQueue(const Type & x);
    Type deQueue();
    Type getHead() const {return array[1];}

private:
    int currentSize;
    Type * array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
};

template < class Type >
void priorityQueue < Type > :: enQueue(const Type & x) {
    if (currentSize == maxSize - 1)
        doubleSpace();
    int hole = ++currentSize;
    for (; hole > 1 && x < array[hole / 2]; hole /= 2) {
        array[hole] = array[hole / 2];
    }
    array[hole] = x;
}

template < class Type >
Type priorityQueue < Type > :: deQueue() {
    Type minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return minItem;
}

template < class Type >
void priorityQueue < Type > :: percolateDown(int hole) {
    int child;
    Type tmp = array[hole];

    for (; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;
        if (child != currentSize && array[child + 1] < array[child])
            child++;
        if (array[child] < tmp) {
            array[hole] = array[child];
        } else {
            break;
        }
    }
    array[hole] = tmp;
}

template < class Type >
void priorityQueue < Type > :: buildHeap() {
    for (int i = currentSize / 2; i > 0; i--)
        percolateDown(i);
}

template < class Type >
priorityQueue < Type > :: priorityQueue(const Type * items, int size)
    :maxSize(size + 1), currentSize(size)
{
    array = new Type [maxSize];
    for (int i = 0; i < size; i++)
        array[i + 1] = items[i];
    buildHeap();
}

template < class Type >
void priorityQueue < Type > :: doubleSpace() {
    Type * tmp = array;

    maxSize *= 2;
    array = new Type [maxSize];

    for (int i = 0; i <= currentSize; ++i)
        array[i] = tmp[i];

    delete [] tmp;
}

template < class Type >
int seqSearch(vector < Type > & data, const Type & x) {
    data[0] = x;
    int i;
    for (i = data.size() + 1; x != data[i]; --i);
    return i;
}

template < class Type >
int binarySearch(const vector < Type > & data, const Type & x) {
    int low = 1, high = data.size() + 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x == data[mid]) {
            return mid;
        }
        if (x < data[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return 0;
}

template < class Type >
class BinarySearchTree
{
    private:
        struct BinaryNode
        {
            Type data;
            BinaryNode * left;
            BinaryNode * right;

            BinaryNode(const Type & thedata, BinaryNode * lt, BinaryNode * rt)
                : data(thedata), left(lt), right(rt) {}
        };

    public:
        BinarySearchTree(BinaryNode * t = NULL) {root = t;}
        ~BinarySearchTree();
        bool find(const Type & x) const;
        void insert(const Type & x);
        void remove(const Type & x);

    private:
        BinaryNode * root;

        void insert(const Type & x, BinaryNode * & t);
        void remove(const Type & x, BinaryNode * & t);
        bool find(const Type & x, BinaryNode * t) const;
        void makeEmpty(BinaryNode * & t);
};

template < class Type >
bool BinarySearchTree < Type > :: find(const Type & x) const {
    return find(x, root);
}

template < class Type >
bool BinarySearchTree < Type > :: find(const Type & x, BinaryNode * t) const {
    if (t == NULL)
        return false;
    else if (x < t -> data)
        return find(x, t -> left);
    else if (t -> data < x)
        return find(x, t -> right);
    else
        return true;
}

template < class Type >
void BinarySearchTree < Type > :: insert(const Type & x) {
    insert(x, root);
}

template < class Type >
void BinarySearchTree < Type > :: insert(const Type & x, BinaryNode * & t) {
    if (t == NULL)
        t = new BinaryNode(x, NULL, NULL);
    else if (x < t -> data)
        insert(x, t -> left);
    else if (t -> data < x)
        insert(x, t -> right);
}

template < class Type >
void BinarySearchTree < Type > :: remove(const Type & x) {
    remove(x, root);
}

template < class Type >
void BinarySearchTree < Type > :: remove(const Type & x, BinaryNode * & t) {
    if (t == NULL)
        return;
    if (x < t -> data)
        remove(x, t -> left);
    else if (t -> data < x)
        remove(x, t -> right);
    else if (t -> left != NULL && t -> right != NULL) {
        BinaryNode * tmp = t -> right;
        while (tmp -> left != NULL) {
            tmp = tmp -> left;
        }
        t -> data = tmp -> data;
        remove(t -> data, t -> right);
    } else {
        BinaryNode * oldNode = t;
        t = (t > left != NULL) ? t -> left : t -> right;
        delete oldNode;
    }
}

template < class Type >
class hashTable
{
    public:
        virtual bool find(const Type & x) const = 0;
        virtual bool insert(const Type & x) = 0;
        virtual bool remove(const Type & x) = 0;

    protected:
        int (*key)(const Type &x);
        static int defaultKey(const int & k) {return k;}
};

template < class Type >
class closeHashTable: public hashTable < Type >
{
    private:
        struct node
        {
            Type data;
            int state;

            node() {state = 0;}
        };

        node * array;
        int size;
    public:
        closeHashTable(int length, int (*f)(const Type &x));
        ~closeHashTable() {delete [] array;}
        bool find(const Type & x) const;
        bool insert(const Type & x);
        bool remove(const Type & x);

        void rehash();
};

template < class Type >
closeHashTable < Type > :: closeHashTable(int length, int (*f)(const Type &x)) {
    size = length;
    array = new node[size];
    key = f;
}

template < class Type >
bool closeHashTable < Type > :: insert(const Type & x) {
    int initPos, pos;

    initPos = pos = key(x) % size;
    do {
        if (array[pos].state != 1) {
            array[pos].data = x;
            array[pos].state = 1;
            return true;
        }
        if (array[pos].state == 1 && array[pos].data == x) {
            return true;
        }
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return false;
}

template < class Type >
bool closeHashTable < Type > :: remove(const Type & x) {
    int initPos, pos;

    initPos = pos = key(x) % size;
    do {
        if (array[pos].state == 0) {
            return false;
        }
        if (array[pos].state == 1 && array[pos].data == x) {
            array[pos].state = 2;
            return true;
        }
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return false;
}

template < class Type >
bool closeHashTable < Type > :: find(const Type & x) const {
    int initPos, pos;

    initPos = pos = key(x) % size;
    do {
        if (array[pos].state == 0)
            return false;
        if (array[pos].state == 1 && array[pos].date == x)
            return true;
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return false;
}

template < class Type >
void closeHashTable < Type > :: rehash() {
    node * tmp = array;

    array = new node[size];
    for (int i = 0; i < size; ++i) {
        if (tmp[i].state == 1)
            insert(tmp[i].data);
    }
    delete [] tmp;
}

template < class Type >
class openHashTable: public hashTable < Type >
{
    private:
        struct node
        {
            Type data;
            node * next;

            node(const Type & d) {data = d; next = NULL;}
            node() {next = NULL;}
        };

        node ** array;
        int size;

    public:
        openHashTable(int length, int (*f)(const Type &x));
        ~openHashTable();
        bool find(const Type & x) const;
        bool insert(const Type & x);
        bool remove(const Type & x);
};

template < class Type >
openHashTable < Type > :: openHashTable(int length, int (*f)(const Type & x)) {
    size = length;
    array = new node * [size];
    key = f;
    for (int i = 0; i < size; ++i)
        array[i] = new node;
}

template < class Type >
openHashTable < Type > :: ~openHashTable() {
    node * p, * q;
    for (int i = 0; i < size; ++i) {
        p = array[i];
        do {
            q = p -> next;
            delete p;
            p = q;
        } while (p != NULL);
    }
    delete [] array;
}

template < class Type >
bool openHashTable < Type > :: insert(const Type & x) {
    int pos;
    node * p;
    pos = key(x) % size;
    p = array[pos] -> next;
    while (p != NULL && !(p -> data == x)) {
        p = p -> next;
    }
    if (p == NULL) {
        p = new node (x);
        p -> next = array[pos] -> next;
        array[pos] -> next = p;
        return true;
    }
    return false;
}

template < class Type >
bool openHashTable < Type > :: remove(const Type & x) {
    int pos;
    node *p, *q;

    pos = key(x) % size;
    p = array[pos];
    while (p -> next != NULL && !(p -> next -> data == x)) {
        p = p -> next;
    }
    if (p -> next == NULL)
        return false;
    else {
        q = p -> next;
        p -> next = q -> next;
        delete q;
        return true;
    }
}

template < class Type >
bool openHashTable < Type > :: find(const Type & x) const {
    int pos;
    node * p;

    pos = key(x) % size;
    p = array[pos];
    while (p -> next != NULL && !(p -> next -> data == x)) {
        p = p -> next;
    }
    if (p -> next != NULL) {
        return true;
    } else {
        return false;
    }
}

template < class T >
void shellSort(T a[], int size) {
    int step, i, j;
    T tmp;

    for (step = size / 2; step > 0; step /= 2) {
        for (i = step; i < size; ++i) {
            tmp = a[i];
            for (j = i - step; j >= 0 && a[j] > tmp; j -= step)
                a[j + step] = a[j];
            a[j + step] = tmp;
        }
    }
}

template < class T >
void heapSort(T a[], int size) {
    int i;
    T tmp;

    for (i = size / 2 - 1; i >= 0; i--) {
        percolateDown(a, i, size);
    }

    for (i = size - 1; i > 0; --i) {
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        percolateDown(a, 0, i);
    }
}

template < class T >
void percolateDown(T a[], int hole, int size) {
    int child;
    T tmp = a[hole];

    for (; hole * 2 + 1 < size; hole = child) {
        child = hole * 2 + 1;
        if (child != size - 1 && a[child + 1] > a[child])
            child++;
        if (a[child] > tmp)
            a[hole] = a[child];
        else
            break;
    }
    a[hole] = tmp;
}

template < class T >
void bubbleSort(T a[], int size) {
    int i, j;
    T tmp;
    bool flag;

    for (i = 1; i < size; ++i) {
        flag = false;
        for (j = 0; j < size - 1; ++j) {
            if (a[j + 1] < a[j]) {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                flag = true;
            }
        }
        if (!flag)
            break;
    }
}

template < class T >
void quickSort(T a[], int low, int high) {
    int mid;
    if (low >= high)
        return;
    mid = divide(a, low, high);
    quickSort(a, low, mid - 1);
    quickSort(a, mid + 1, high);
}

template < class T >
void quickSort(T a[], int size) {
    quickSort(a, 0, size - 1);
}

template < class T >
int divide(T a[], int low, int high) {
    T k = a[low];
    do {
        while (low < high && a[high] >= k)
            --high;
        if (low < high) {
            a[low] = a[high];
            ++low;
        }
        while (low < high && a[low] >= k)
            ++low;
        if (low < high) {
            a[high] = a[low];
            --high;
        }
    } while (low != high);
    a[low] = k;
    return low;
}

template < class T >
void merge(T a[], int left, int mid, int right) {
    T * tmp = new T[right - left + 1];

    int i = left, j = mid, k = 0;

    while (i < mid && j <= right) {
        if (a[i] < a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
        }
    }

    while (i < mid) {
        tmp[k++] = a[i++];
    }
    while (j <= right) {
        tmp[k++] = a[j++];
    }

    for (i = 0, k = left; k <= right;) {
        a[k++] = tmp[i++];
    }
    delete [] tmp;
}

template < class T >
void mergeSort(T a[], int left, int right) {
    int mid = (left + right) / 2;

    if (left == right)
        return;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid + 1, right);
}

template < class T >
void mergeSort(T a[], int size) {
    mergeSort(a, 0, size - 1);
}

template < class TypeOfEdge >
class graph
{
    public:
        virtual bool insert(int u, int v, TypeOfEdge w) = 0;
        virtual bool remove(int u, int v) = 0;
        virtual bool exist(int u, int v) const = 0;
        virtual int numOfVer() const {return Vers;}
        virtual int numOfEdge() const {return Edges;}

    protected:
        int Vers, Edges;
};

template < class TypeOfVer, class TypeOfEdge >
class adjMatrixGraph: public graph < TypeOfVer > {
    public:
        adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);
        bool insert(int u, int v, TypeOfEdge w);
        bool remove(int u, int v);
        bool exist(int u, int v) const;
        ~adjMatrixGraph();

    private:
        TypeOfEdge ** edge;
        TypeOfVer * ver;
        TypeOfEdge noEdge;
};

template < class TypeOfVer, class TypeOfEdge >
adjMatrixGraph < TypeOfVer, TypeOfEdge > :: adjMatrixGraph(int vSize,
        const TypeOfVer d[], TypeOfEdge noEdgeFlag)
{
    int i, j;

    Vers = vSize;
    Edges = 0;
    noEdge = noEdgeFlag;

    ver = new TypeOfVer [vSize];
    for (i = 0; i < vSize; ++i)
        ver[i] = d[i];

    edge = new TypeOfEdge * [vSize];
    for (i = 0; i < vSize; ++i) {
        edge[i] = new TypeOfEdge [vSize];
        for (j = 0; j < vSize; ++j)
            edge[i][j] = noEdge;
        edge[i][i] = 0;
    }
}

template < class TypeOfVer, class TypeOfEdge >
adjMatrixGraph < TypeOfVer, TypeOfEdge > :: ~adjMatrixGraph() {
    delete [] ver;
    for (int i = 0; i < Vers; ++i)
        delete [] edge[i];
    delete [] edge;
}

template < class TypeOfVer, class TypeOfEdge >
bool adjMatrixGraph < TypeOfVer, TypeOfEdge > :: insert(int u, int v, TypeOfEdge w) {
    if (u < 0 || u > Vers - 1 || v < 0 || v > Vers - 1)
        return false;
    if (edge[u][v] != noEdge)
        return false;
    edge[u][v] = w;
    ++Edges;
    return true;
}

template < class TypeOfVer, class TypeOfEdge >
bool adjMatrixGraph < TypeOfVer, TypeOfEdge > :: remove(int u, int v) {
    if (u < 0 || u > Vers - 1 || v < 0 || v > Vers - 1)
        return false;
    if (edge[u][v] == noEdge)
        return false;
    edge[u][v] = noEdge;
    --Edges;
    return true;
}

template < class TypeOfVer, class TypeOfEdge >
bool adjMatrixGraph < TypeOfVer, TypeOfEdge > :: exist(int u, int v) const {
    if (u < 0 || u > Vers - 1 || v < 0 || v > Vers - 1)
        return false;
    if (edge[u][v] == noEdge)
        return false;
    else
        return true;
}

template < class TypeOfVer, class TypeOfEdge >
class adjListGraph: public graph < TypeOfEdge >
{
    public:
        adjListGraph(int vSize, const TypeOfVer d[]);
        bool insert(int u, int v, TypeOfEdge w);
        bool remove(int u, int v);
        bool exist(int u, int v) const;
        ~adjListGraph();

    private:
        struct edgeNode
        {
            int end;
            TypeOfEdge weight;
            edgeNode * next;

            edgeNode(int e, TypeOfEdge w, edgeNode * n = NULL) {
                end = e;
                weight = w;
                next = n;
            }
        };

        struct verNode
        {
            TypeOfVer ver;
            edgeNode * head;

            verNode(edgeNode * h = NULL) {
                head = h;
            }
        };

        verNode * verList;
};

template < class TypeOfVer, class TypeOfEdge >
adjListGraph < TypeOfVer, TypeOfEdge > :: adjListGraph(int vSize, const TypeOfVer d[]) {
    Vers = vSize;
    Edges = 0;

    verList = new verNode[vSize];
    for (int i = 0; i < Vers; ++i)
        verList[i].ver = d[i];
}

template < class TypeOfVer, class TypeOfEdge >
adjListGraph < TypeOfVer, TypeOfEdge > :: ~adjListGraph() {
    int i;
    edgeNode * p;

    for (i = 0; i < Vers; ++i) {
        while ((p = verList[i].head) != NULL) {
            verList[i].head = p -> next;
            delete p;
        }
    }

    delete [] verList;
}

template < class TypeOfVer, class TypeOfEdge >
bool adjListGraph < TypeOfVer, TypeOfEdge > :: insert(int u, int v, TypeOfEdge w) {
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++Edges;
    return true;
}

template < class TypeOfVer, class TypeOfEdge > 
bool adjListGraph < TypeOfVer, TypeOfEdge > :: remove(int u, int v) {
    edgeNode * p = verList[u].head, * q;

    if (p == NULL)
        return false;

    if (p -> end == v) {
        verList[u].head = p -> next;
        delete p;
        --Edges;
        return true;
    }

    while (p -> next != NULL && p -> next -> end != v) {
        p = p -> next;
    }
    if (p -> next == NULL)
        return false;
    q = p -> next;
    p -> next = q -> next;
    delete p;
    --Edges;
    return true;

}

template < class TypeOfVer, class TypeOfEdge >
bool adjListGraph < TypeOfVer, TypeOfEdge > :: exist(int u, int v) const {
    edgeNode * p = verList[u].head;

    while (p != NULL && p -> end != v) {
        p = p -> next;
    }
    if (p == NULL)
        return false;
    else
        return true;
}

template < class TypeOfVer, class TypeOfEdge >
void adjListGraph < TypeOfVer, TypeOfEdge > :: dfs() const {
    bool * visited = new bool [Vers];

    for (int i = 0; i < Vers; ++i)
        visited[i] = false;

    cout << "DFS results:" << endl;

    for (int i = 0; i < Vers; ++i) {
        if (visited[i] == true)
            continue;
        dfs(i, visited);
        cout << endl;
    }
}

template < class TypeOfVer, class TypeOfEdge >
void adjListGraph < TypeOfVer, TypeOfEdge > :: dfs(int start, bool visted[]) const {
    edgeNode * p = verList[start].head;

    cout << verList[start].ver << '\t';
    visted[start] = true;

    while (p != NULL) {
        if (visted[p -> end] == false)
            dfs(p -> end, visited);
        p = p -> next;
    }
}

template < class TypeOfVer, class TypeOfEdge >
void adjListGraph < TypeOfVer, TypeOfEdge > :: bfs() const {
    bool * visted = new bool [Vers];
    int currentNode;
    linkQueue < int > q;
    edgeNode * p;

    for (int i = 0; i < Vers; ++i)
        visted[i] = false;

    cout << "BFS results:";

    for (int i = 0; i < Vers; ++i) {
        if (visted[i] = =true)
            continue;
        q.enQueue(i);
        while (! q.isEmpty()) {
            currentNode = q.deQueue();
            if (visted[currentNode] == true)
                continue;
            cout << verList[currentNode].ver << '\t';
            visited[currentNode] = true;
            p = verList[currentNode].head;
            while (p != NULL) {
                if (visted[p -> end] == false)
                    q.enQueue(p -> end);
                p = p -> next;
            }
        }
        cout << endl;
    }
}

struct EulerNode
{
    int NodeNum;
    EulerNode * next;
    EulerNode(int ver) {NodeNum = ver; next = NULL;}
};

template < class TypeOfVer, class TypeOfEdge >
void adjListGraph < TypeOfVer, TypeOfEdge > :: EulerCircuit(TypeOfVer start) {
    EulerNode * beg, * end, * p, * q, * tb, * te;
    int numOfDegree;
    edgeNode * r;
    verNode * tmp;

    if (Edges == 0) {
        cout << "No Euler Circuit!" << endl;
    }
    for (int i = 0; i < Vers; ++i) {
        numOfDegree = 0;
        r = verList[i].head;
        while (r != 0) {
            ++numOfDegree;
            r = r -> next;
        }
        if (numOfDegree == 0 || numOfDegree % 2) {
            cout << "No Euler Circuit!" << endl;
        }
    }

    int i;
    for (i = 0; i < Vers; ++i) {
        if (verList[i].ver == start) break;
    }
    if (i == Vers) {
        cout << "Start Node doesn't exist!" << endl;
        return;
    }

    tmp = clone();

    beg = EulerCircuit(i, end);

    while (true) {
        p = beg;
        while (p -> next != NULL) {
            if (verList[p -> next -> NodeNum].head != NULL)
                break;
            else
                p = p -> next;
            if (p -> next == NULL)
                break;
            q = p -> next;
            tb = EulerCircuit(q -> NodeNum, te);
            te -> next = q -> next;
            p -> next == tb;
            delete q;
        }
    }

    delete [] verList;
    verList = tmp;

    cout << "Ruler Circuit is :" << endl;
    while (beg != NULL) {
        cout << verList[beg -> NodeNum].ver << '\t';
        p = beg;
        beg = beg -> next;
        delete p;
    }
    cout << endl;
}

template < class TypeOfVer, class TypeOfEdge >
typename adjListGraph < TypeOfVer, TypeOfEdge > :: verNode * adjListGraph < TypeOfVer,
             TypeOfEdge > :: clone() const
{
    verNode * tmp = new verNode [Vers];
    edgeNode * p;

    for (int i = 0; i < Vers; ++i) {
        tmp[i].ver = verList[i].ver;
        p = verList[i].head;
        while (p != NULL) {
            tmp[i].head = new edgeNode(p -> end, p -> weight, tmp[i].head);
        }
    }
}
