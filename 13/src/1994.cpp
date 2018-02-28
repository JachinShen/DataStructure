#include <iostream>

using namespace std;

bool map[505][505] = {0};

void search(int x, int y)
{
    map[x][y] = false;
    if (map[x][y-1])
        search(x, y-1);
    if (map[x][y+1])
        search(x, y+1);
    if (map[x-1][y])
        search(x-1, y);
    if (map[x+1][y])
        search(x+1, y);
}

int main(void)
{
    int N, M;
    cin >> N >> M;
    int tmp;
    unsigned long long ctr = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> tmp;
            if(tmp == 0)
                map[i][j] = true;
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (map[i][j]) {
                ++ctr;
                search(i, j);
            }
        }
    }
    cout << ctr << endl;
    return 0;
}
