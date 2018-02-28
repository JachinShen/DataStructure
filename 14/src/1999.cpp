#include <iostream>
using namespace std;

#define MAX_SIZE 105
int N, M;
int map[MAX_SIZE][MAX_SIZE] = {0};
bool visited[MAX_SIZE][MAX_SIZE] = {0};
int treasure_ctr = 0;
int dp[6][6] = {0};
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct Point {
    int x, y;
    int step, type;
    Point(int i=0, int j=0):
        x(i), y(j), step(0), type(0){}
};

Point start;
Point treasures[5];
int path[5] = {0};

template<class T>
class MyQueue
{
    private:
        T * data;
        int max_size;
        int front, rear;

        void doubleSpace(){
            T * tmp = data;
            data = new T [2 * max_size];
            for (int i = 1; i < max_size; ++i) {
                data[i] = tmp[(front + i) % max_size];
            }

            front = 0;
            rear = max_size - 1;
            max_size *= 2;

            delete [] tmp;
        }
    public:
        MyQueue(int size = 1) {
            data = new T [size];
            max_size = size;
            front = rear = 0;
        } 
        ~MyQueue() {
            delete [] data;
        }
        bool isEmpty() {
            return front == rear;
        }
        void enQueue(const T & x) {
            if ((rear + 1) % max_size == front) {
                doubleSpace();
            }
            rear = (rear + 1) % max_size;
            data[rear] = x;
        }
        T deQueue() {
            front = (front + 1) % max_size;
            return data[front];
        }
        T getHead() {
            return data[(front + 1) % max_size];
        }
};

int search(Point & begin, Point & end) {
    MyQueue<Point> queue;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            visited[i][j] = false;
        }
    }
    begin.step = 0;
    queue.enQueue(begin);
    while(!queue.isEmpty()) {
        Point now = queue.deQueue();
        visited[now.x][now.y] = true;
        Point next;
        for (int i = 0; i < 4; ++i) {
            next.x = now.x + dx[i];
            next.y = now.y + dy[i];
            if (next.x >= 1
                    && next.x <= N
                    && next.y >= 1
                    && next.y <= M) {
                if (visited[next.x][next.y])
                    continue;
                next.type = map[next.x][next.y];
                visited[next.x][next.y] = true;
                if (next.type != -1) {
                    next.step = now.step + 1;
                    if (next.x == end.x && next.y == end.y)
                        return next.step;
                    queue.enQueue(next);
                }
            }
        }
    }
    return -1;
}

void swap(int *a,int i,int j)  
{  
    a[i]^=a[j];  
    a[j]^=a[i];  
    a[i]^=a[j];  
}  
  
void reverse(int a[],int i,int j)  
{  
    for(; i<j; ++i,--j) {  
        swap(a,i,j);  
    }  
}  

int main(void)
{
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> map[i][j];
            if (map[i][j] == 2) {
                start.x = i;
                start.y = j;
                start.step = 0;
                start.type = 2;
            }
            if (map[i][j] == 1) {
                treasures[treasure_ctr].x = i;
                treasures[treasure_ctr].y = j;
                path[treasure_ctr] = treasure_ctr;
                ++treasure_ctr;
            }
        }
    }

    for (int i = 0; i < treasure_ctr; ++i) {
        dp[5][i] = search(start, treasures[i]);
        if (dp[5][i] == -1) {
            cout << -1 << endl;
            return 0;
        }
    }

    for (int i = 0; i < treasure_ctr; ++i) {
        for (int j = i + 1; j < treasure_ctr; ++j) {
            dp[i][j] = search(treasures[i], treasures[j]);
            dp[j][i] = dp[i][j];
            if (dp[i][j] == -1) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    if (treasure_ctr == 1) {
        cout << dp[5][0] << endl;
        return 0;
    }

    int closest = 0x8fff;
    if (treasure_ctr == 2) {
        int distance1 = dp[5][0] + dp[0][1];
        int distance2 = dp[5][1] + dp[1][0];
        cout << (distance1 < distance2 ? distance1 : distance2) << endl;
        return 0;
    }


    bool end = false;
    while (!end) {  
        //cout << path[0] << path[1] << path[2] << path[3] << path[4] << endl;
        int distance = dp[5][path[0]];
        for (int i = 1; i < treasure_ctr; ++i) {
            distance += dp[path[i]][path[i-1]];
        }
        closest = closest < distance ? closest : distance;
        //cout << closest << endl;
        int i,j;  
        for (i = treasure_ctr-2; i >= 0; --i) {  
            if (path[i] < path[i+1]) 
                break;  
            else if (i == 0)
                end = true;
        }  

        for (j = treasure_ctr-1; j > i; --j) {  
            if(path[j] > path[i]) 
                break;  
        }  

        swap(path,i,j);  
        reverse(path,i+1,treasure_ctr-1);  
    }  

    cout << closest << endl;

    return 0;
}
