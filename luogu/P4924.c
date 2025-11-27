#include "stdio.h"
/*https://www.luogu.com.cn/problem/P4924*/
int main(){
    int m,n;
    scanf ("%d %d",&n,&m);
    int matrix[n][n];
    int x = 1;
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matrix[i][j] = x++;
        }
    }

    int operation[m][4];
    for (int i = 0; i < m; i++){
        for (int j = 0; j < 4; j++){
            scanf("%d",&operation[i][j]);
        }
    }
    for(int i = 0; i < m; i++){
        int cx = operation[i][0] - 1;  // 旋转的横坐标
        int cy = operation[i][1] - 1;  // 旋转的中心点
        int len = operation[i][2]; // 旋转的长度
        int ro = operation[i][3]; // 0: 顺时针 1: 逆时针
        int L = 2*len+1;
        int temp[L][L];
        for(int p = 0; p < L; p++){
            for(int q = 0; q < L; q++){
                temp[p][q] = matrix[cx - len + p][cy - len + q];
            }
        }
        if (ro == 0){
            for (int p = 0; p < L; p++){
                for(int q = 0; q < L; q++){
                    matrix[cx - len + p][cy - len + q] = temp[L - 1 - q][p];
                }
            }
        }else{
            for (int p = 0; p < L; p++){
                for(int q = 0; q < L; q++){
                    matrix[cx - len + p][cy - len + q] = temp[q][L - 1 - p];
                }
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

}


/*
sample temp
    j0                j5
i5



i0

i 0                  i 5
x1y1 x2y1 x3y1  x4y1 x5y1 j 0
x1y2 x2y2 x3y2  x4y2 x5y2
x1y3 x2y3 x3y3* x4y3 x5y3
x1y4 x2y4 x3y4  x4y4 x5y4
x1y5 x2y5 x3y5  x4y5 x5y5 j 5

rotation r;

先转最外层 坐标变换 x y -> y r-1-x

先镜像 再交换

或者先交换 在镜像
*/