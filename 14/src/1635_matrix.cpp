#include <iostream>
using namespace std;

#include <stdlib.h>
#define DEBUG

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned char uchar;

template< class TypeOfVer, class TypeOfEdge >
class adjMatrixGraph
{
    private:
        ulong Vers, Edges;
        TypeOfVer * ver;
        TypeOfEdge * * edge;
        TypeOfEdge noEdge;

    public:
        adjMatrixGraph(ulong vSize, const TypeOfEdge noEdgeFlag) {
            Vers = vSize;
            Edges = 0;
            noEdge = noEdgeFlag;

            ver = new TypeOfVer[vSize];
            edge = new TypeOfEdge * [vSize];
            for (ulong i = 0; i < Vers; ++i) {
                ver[i] = i;
                edge[i] = new TypeOfEdge [vSize];
                for (ulong j = 0; j < vSize; ++j)
                    edge[i][j] = noEdge;
                edge[i][i] = 0;
            }
        }
        bool insert(ulong u, ulong v, TypeOfEdge w) {
            if (u < 0
                    || u > Vers - 1
                    || v < 0
                    || v > Vers - 1)
                return false;
            if (edge[u][v] != noEdge)
                return false;
            edge[v][u] = edge[u][v] = w;
            ++ Edges;
            return true;
        }
        bool remove(ulong u, ulong v) {
            if (u < 0
                    || u > Vers - 1
                    || v < 0
                    || v > Vers - 1)
                return false;
            if (edge[u][v] == noEdge)
                return false;
            edge[u][v] = edge[u][v] = noEdge;
            -- Edges;
            return true;
        }
        bool exist(ulong u, ulong v) const {
            if (u < 0
                    || u > Vers - 1
                    || v < 0
                    || v > Vers - 1)
                return false;
            if (edge[u][v] == noEdge)
                return false;
            else 
                return true;
        }
        ~adjMatrixGraph() {
            delete [] ver;
            for (ulong i = 0; i < Vers; ++i)
                delete [] edge[i];
            delete [] edge;
        }
        void search(ulong end) const {
            bool * flag = new bool [Vers];
            ulong * lowCost = new ulong[Vers];

            ulong min;
            ulong v_min = 0;
            ulong i, j;
            
            for (i = 0; i < Vers; ++i) {
                flag[i] = false;
                lowCost[i] = edge[0][i];
            }

            lowCost[0] = 0;
            flag[0] = true;

            for (i = 0; i < Vers && v_min != end; ++i) {
                min = noEdge;
                v_min = 0;
                for (j = 0; j < Vers; ++j) {
                    if (!flag[j] && lowCost[j] < min) {
                        v_min = j;
                        min = lowCost[j];
                    }
                }
                flag[v_min] = true;
                for (j = 0; j < Vers; ++j) {
                    if (!flag[j] && edge[v_min][j] < noEdge) {
                        if (lowCost[v_min] + edge[v_min][j] < lowCost[j]) {
                            lowCost[j] = lowCost[v_min] + edge[v_min][j];
                        }
                    }
                }

            }

            cout << lowCost[v_min] << endl;

            delete [] flag;
            delete [] lowCost;
        }
};

int main(void)
{
    ulong N, M;
    cin >> N >> M;
    adjMatrixGraph<ulong, uchar>  route(N, 255);
    ulong v_start, v_end;
    ulong transport;
    srand(1);
    for (ulong i = 0; i < M; ++i) {
#ifdef DEBUG
        v_start = rand() % N + 1;
        v_end = rand() % N + 1;
        transport = rand() % 3 + 1;
        cout << v_start << "\t" << v_end << "\t" << transport << endl;
#else
        cin >> v_start >> v_end >> transport;
#endif
        route.insert(v_start-1, v_end-1, transport);
    }
    route.search(N-1);
    return 0;
}
