#include "stdio.h"
#include "stdlib.h"

//本题与3相同
int main(){
    int n,m,q,k;
    scanf("%d %d %d %d",&n,&m,&q,&k);
    int a[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a[i][j] = 0;
        }
    }
    for(int i = 0; i < q; i++){
        int x;
        scanf("%d",&x);
        for(int j = 0; j < m ; j++){
            a[x-1][j] += 1;
        }
    }
    for (int i = 0; i < k; i++){
        int y;
        scanf("%d",&y);
        for(int j = 0; j < n; j++){
            a[j][y-1] += 2;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(a[i][j] == 0){
                printf("0");
            }else if(a[i][j] == 1){
                printf("-");
            }else if(a[i][j] == 2){
                printf("|");
            }else if(a[i][j] == 3){
                printf("+");
            }
        }
        printf("\n");

    }
}