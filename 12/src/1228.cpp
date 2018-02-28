#include <iostream>

using namespace std;

long long odd_ctr = 0;
int zero_ctr[405];
int len = 0;
bool arr[405][405] = {0};
void count(bool arr[], int n){
    int now = 0;
    for (int i=0; i<n; i++){
        now++;
        if (arr[i] == 1){
            zero_ctr[len++] = now;
            now = 0;
        }
    }
    if (len == 0) return;
    zero_ctr[len++] = ++now;
    for (int i=0; i<len; i++){
        for (int j=i+1; j<len; j+=2){
            odd_ctr += (zero_ctr[i] * zero_ctr[j]);
        }
    }
    len = 0;
    return;
}
int main()
{
    int n;
    cin >> n;
    int tmp;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin >> tmp;
            arr[i][j] = tmp%2;
        }
    }
    for (int i=0; i<n; i++){
        count(arr[i], n);
        for (int j=i+1; j<n; j++){
            for (int k=0; k<n; k++){
                arr[i][k] = (arr[i][k]+arr[j][k])%2;
            }
            count(arr[i], n);
        }
    }
    cout << odd_ctr << ' ' << (long long) n * n * (n + 1) * (n + 1) / 4 - odd_ctr << endl;
    return 0;
}
