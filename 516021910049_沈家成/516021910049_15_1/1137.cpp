#include <iostream>
using namespace std;

class Union
{
private:
    int * prev;
    long long * ctr;
    int size;
public:
    Union (int n) {
        prev = new int [n + 1];
        ctr = new long long [n + 1];
        size = n;
        for (int i = 1; i <= n; ++i) {
            prev[i] = i;
            ctr[i] = 1;
        }
    }
    ~Union () {
        if (prev)
            delete [] prev;
        if (ctr)
            delete [] ctr;
    }

    int find(int x) {
        int r = x;
        while (r != prev[r])
            r = prev[r];
        int i = x, j;
        while (i != r) {
            j = prev[i];
            prev[i] = r;
            i = j;
        }
        return r;
    }

    void join(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            ctr[fy] += ctr[fx];
            prev[fx] = fy;
        }
    }

    long long getLinkEdges(int b, int e) {
        //cout << ctr[find(b)] << " " << ctr[find(e)] << endl;
        return (ctr[find(b)] * ctr[find(e)] - 1);
    }

};


template< class T >
class QuickSort
{
    private:
        void quickSort(T a[], long low, long high)
        {
            long mid;
            if (low >= high)
                return;
            mid = divide(a, low, high);
            quickSort(a, low, mid - 1);
            quickSort(a, mid + 1, high);
        }
        long divide(T a[], long low, long high)
        {
            T k = a[low];
            do {
                while (low < high) {
                    if (a[high] >= k) {
                        --high;
                    } else 
                        break;
                }
                if (low < high) {
                    a[low] = a[high];
                    ++low;
                }
                while (low < high) {
                    if (a[low] <= k) {
                        ++low;
                    } else 
                        break;
                }
                if (low < high) {
                    a[high] = a[low];
                    --high;
                }
            } while (low != high);
            a[low] = k;
            return low;
        }
    public:
        QuickSort()
        {
        }
        void quickSort(T a[], long size)
        {
            quickSort(a, 0, size - 1);
        }
};

struct edgeNode
{
    int begin, end, value;
    edgeNode()
        :begin(0), end(0), value(0){};
    edgeNode(int b, int e, int v)
        :begin(b), end(e), value(v){};
    bool operator < (edgeNode & e2) {
        return value < e2.value;
    }
    bool operator > (edgeNode & e2) {
        return value > e2.value;
    }
    bool operator <= (edgeNode & e2) {
        return value <= e2.value;
    }
    bool operator >= (edgeNode & e2) {
        return value >= e2.value;
    }
};

int main(void)
{
    int t, n;
    cin >> t;
    edgeNode * edges;
    QuickSort<edgeNode> quick_sort;
    for (int i = 0; i < t; ++i) {
    long long result = 0;
        cin >> n;
        edges = new edgeNode [n];
        Union vers(n);
        for (int j = 1; j < n; ++j) {
            cin >> edges[j].begin >> edges[j].end >> edges[j].value;
            result += edges[j].value;
            //vers.join(edges[j].begin, edges[j].end);
        }
        //cout << result << endl;
        quick_sort.quickSort(edges + 1, n - 1);
        for (int j = 1; j < n; ++j) {
            //cout << edges[j].value;
            result += vers.getLinkEdges(edges[j].begin, edges[j].end) * (edges[j].value + 1);
            vers.join(edges[j].begin, edges[j].end);
        }
        cout << result << endl;
    }
    return 0;
}
