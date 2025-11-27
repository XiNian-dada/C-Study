#include "stdio.h"
#include "stdlib.h"
/*
 * 题目描述：Zig-Zag模式填充矩阵
 * 
 * 难度：中等+
 * 
 * 输入：
 * - 一行：两个整数m, n，表示矩阵维度，以空格隔开
 * 
 * 输出：
 * - m行n列的矩阵：按Zig-Zag顺序填充数字1到m*n
 * - 矩阵元素间用1个空格隔开
 * 
 * 要求：
 * - Zig-Zag填充规则：沿反对角线方向交替填充
 *   奇数对角线：从左下向右上填充
 *   偶数对角线：从右上向左下填充
 * 
 * 示例：
 * 输入: 3 3
 * 输出:
 * 1 2 6
 * 3 5 7
 * 4 8 9
 * 
 * 输入: 2 3
 * 输出:
 * 1 2 5
 * 3 4 6
 * 
 * 解释:
 * 3x3矩阵填充顺序：
 * 第1条对角线(↙): 1
 * 第2条对角线(↗): 2,3  
 * 第3条对角线(↙): 4,5,6
 * 第4条对角线(↗): 7,8
 * 第5条对角线(↙): 9
 * 
 * 2x3矩阵填充顺序：
 * 第1条对角线: 1
 * 第2条对角线: 2,3
 * 第3条对角线: 4,5  
 * 第4条对角线: 6
 * 
 * 约束：
 * - 1 ≤ m, n ≤ 100
 * - 输出格式：元素间用1个空格分隔
 */
int** matrix;
int m,n;      
int max_num = 0;

void process(int x,int y,int direction,int fill_num){
    if (fill_num > max_num) {
        return;
    }

    matrix[x][y] = fill_num;

    int next_x = x;
    int next_y = y;
    int next_direction = direction;

    switch(direction){
        case 1:{ 
            next_y = y + 1;
            if (next_y >= n) return; 
            next_direction = 2; 
            break;
        }
        case 2:{ 
            next_x = x + 1;
            next_y = y - 1;

            if (next_x >= m) { 
                next_x = x;
                next_y = y + 1; 
                if (next_y >= n) return; 
                next_direction = 4; 
            } else if (next_y < 0) { 
                next_x = x + 1; 
                next_y = y;
                if (next_x >= m) return;
                next_direction = 4; 
            } else {
                next_direction = 2; 
            }
            break;
        }
        case 3:{ 
            next_x = x + 1;
            if (next_x >= m) return; 
            next_direction = 4; 
            break;
        }
        case 4:{ 
            next_x = x - 1;
            next_y = y + 1;

            if (next_x < 0) { 
                if (next_y >= n) { 
                    next_x = x + 1; 
                    next_y = y;
                    if (next_x >= m) return;
                    next_direction = 2; 
                } else {
                    next_x = x; 
                    next_y = y + 1;
                    next_direction = 2; 
                }
            } else if (next_y >= n) { 
                next_x = x + 1; 
                next_y = y;
                if (next_x >= m) return;
                next_direction = 2; 
            } else {
                next_direction = 4; 
            }
            break;
        }

    }

    process(next_x, next_y, next_direction, fill_num + 1);
}

int main(){
    scanf("%d %d",&m,&n);
    
    max_num = m*n;
    matrix = (int**)malloc(sizeof(int*)*m);
    for(int i=0;i<m;i++){
        matrix[i] = (int*)malloc(sizeof(int)*n);
    }
    if(n == 1){
        for(int i=1;i<=m;i++){
            printf("%d\n",i);
        }
        return 0;
    }
    process(0, 0, 1, 1); 

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
