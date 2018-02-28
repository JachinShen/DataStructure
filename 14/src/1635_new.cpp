#include <iostream>
using namespace std;
#include <stdlib.h>
//#define DEBUG

//typedef unsigned long long;
typedef unsigned int uint;

template< class Type >
class AATree
{
    private:
        struct AANode {
            Type data;
            AANode * left;
            AANode * right;
            int level;

            AANode (Type & thedata, AANode * lt, AANode * rt, int lv = 1)
                :data(thedata), left(lt), right(rt), level(lv) {}
        };

        AANode * root;

        void insert(Type & x, AANode * & t) {
            if (t == NULL)
                t = new AANode(x, NULL, NULL);
            else if (x < t->data)
                insert(x, t->left);
            else if (t->data < x)
                insert(x, t->right);
            else
                return;

            LL(t);
            RR(t);
        }
        void remove(Type & x, AANode * & t) {
            if (t == NULL)
                return;
            if (x < t->data)
                remove(x, t->left);
            else if (t->data < x)
                remove(x, t->right);
            else if (t->left != NULL && t->right != NULL) {
                AANode * tmp = t->right;
                while (tmp->left != NULL)
                    tmp = tmp->left;
                t->data = tmp->data;
                remove(t->data, t->right);
            }
            else {
                AANode * oldNode = t;
                t = (t->left != NULL) ? t->left : t->right;
                delete oldNode;
                return;
            }

            if (t->left == NULL || t->right == NULL)
                t->level = 1;
            else
                t->level = min(t->left->level, t->right->level) + 1;
            if (t->right != NULL && t->right->level > t->level)
                t->right->level = t->level;
            LL(t);
            if (t->right != NULL)
                LL(t->right);
            if (t->right != NULL && t->right->right != NULL)
                LL(t->right->right);
            RR(t);
            if (t->right != NULL)
                RR(t->right);
        }
        void LL(AANode * & t) {
            if (t->left != NULL && t->left->level == t->level) {
                AANode * t1 = t->left;
                t->left = t1->right;
                t1->right = t;
                t = t1;
            }
        }
        void RR(AANode * & t) {
            if (t->right != NULL && t->right->right != NULL
                   && t->right->right->level == t->level) {
                AANode * t1 = t->right;
                t->right = t1->left;
                t1->left = t;
                t = t1;
                t->level ++;
            }
        }

    public:
        AATree(AANode * t = NULL) {
            root = t;
        }
        ~AATree() {

        }
        void insert(Type x) {
            insert(x, root);
        }
        void remove(Type x) {
            remove(x, root);
        }
        Type minimum() {
            AANode * p = root;
            if (p == NULL)
                return Type(0,0);
            while(p->left != NULL)
                p = p->left;
            return p->data;
        }
};

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
            TypeOfEdge * distance = new TypeOfEdge[Vers];
            bool * known = new bool [Vers];

            long u, i ,j;
            edgeNode * p;
            TypeOfEdge min;
            costNode min_node(0, 0);

            AATree< costNode > tree;

            for (i = 0; i < Vers; ++i) {
                known[i] = false;
                distance[i] = noEdge;
            }
            distance[0] = 0;

            for (i = 0; i< Vers; ++i) {
                //min = noEdge;
                //for (j = 0; j < Vers; ++j) {
                    //if (!known[j] && distance[j] < min) {
                        //min = distance[j];
                        //u = j;
                    //}
                //}
                min_node = tree.minimum();
                tree.remove(min_node);
                u = min_node.ver;
                //cout << "go to:" << u+1 << endl;
                //if (u == 103) {
                    //cout << "debug" ;
                //}
                min = min_node.cost;
                if (u == end)
                    break;
                known[u] = true;
                for (p = verList[u].head; p != NULL; p = p->next) {
                    if (known[p->end])
                        continue;
                    if (distance[p->end] == noEdge) {
                        distance[p->end] = min + p->weight;
                        tree.insert(costNode(distance[p->end], p->end));
                        continue;
                    }
                    if (distance[p->end] > min + p->weight) {
                        tree.remove(costNode(distance[p->end], p->end));
                        distance[p->end] = min + p->weight;
                        tree.insert(costNode(distance[p->end], p->end));
                    }
                }
            }
            cout << distance[end] << endl;
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
            costNode(TypeOfEdge c, long v):cost(c), ver(v){};
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

