#include "stdio.h"
/*https://www.luogu.com.cn/problem/P1004*/

int main(){
    int matrix[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){ 
            matrix[i][j]=0;
        }
    }
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int a,b,c;
        scanf("%d %d ",&a,&b,&c);
        matrix[a][b]=c;
    }
}