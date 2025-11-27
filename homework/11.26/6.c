#include "stdio.h"
#include "stdlib.h"
int n,m;
char** a;
/*
 * 题目描述：走迷宫（环形移动）
 * 
 * 难度：中等-
 * 
 * 输入：
 * - 第1行：整数N, M，表示矩阵大小
 * - 接下来N行：每行M个字符（U,D,L,R），表示移动方向矩阵
 * - 第N+2行：整数Q，表示询问次数
 * - 接下来Q行：每行x0, y0, step，表示初始坐标和移动步数
 * 
 * 输出：
 * - Q行：每行两个整数，表示移动step步后的坐标
 * 
 * 移动规则：
 * - U：向上移动，如果x=1则跳到(N,y)
 * - D：向下移动，如果x=N则跳到(1,y)  
 * - L：向左移动，如果y=1则跳到(x,M)
 * - R：向右移动，如果y=M则跳到(x,1)
 * 
 * 示例：
 * 输入:
 * 5 5
 * UDRRU
 * LRDDL
 * DLUUD
 * RULLR
 * UDURU
 * 5
 * 1 1 1
 * 2 1 2
 * 3 3 10
 * 4 2 99
 * 3 5 3000
 * 输出:
 * 5 1
 * 2 4
 * 3 3
 * 4 1
 * 3 2
 * 
 * 解释:
 * 第1次询问：(1,1)根据U向上移动，x=1所以跳到(5,1)
 * 第2次询问：(2,1)根据L向左移动，y=1所以跳到(2,5)，再根据L向左跳到(2,4)
 * 
 * 约束：
 * - 1 ≤ N, M, Q ≤ 50
 * - 1 ≤ step ≤ 3000
 * - 矩阵字符只包含U,D,L,R
 * - 注意环形边界的处理
 */
void process(char c,int x_now,int y_now,int step){
    char c_now = c;
    if(step==0){
        printf("%d %d\n",x_now+1,y_now+1);
        return;  
    }
    switch(c_now){
        case 'U':{
            if(x_now-1>=0){
                process(a[x_now-1][y_now],x_now-1,y_now,step-1);
            }else{
                process(a[n-1][y_now],n-1,y_now,step-1); 
            }
            break;  
        }
        case 'D':{
            if(x_now+1<n){
                process(a[x_now+1][y_now],x_now+1,y_now,step-1);
            }else{
                process(a[0][y_now],0,y_now,step-1);
            }
            break;  
        }
        case 'L':{
            if(y_now-1>=0){
                process(a[x_now][y_now-1],x_now,y_now-1,step-1);
            }else{
                process(a[x_now][m-1],x_now,m-1,step-1);  
            }
            break;  
        }
        case 'R':{
            if(y_now+1<m){
                process(a[x_now][y_now+1],x_now,y_now+1,step-1);
            }else{
                process(a[x_now][0],x_now,0,step-1);
            }
            break;  
        }
    }
}

int main(){
    scanf("%d %d",&n,&m);
    a = (char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++){
        a[i] = (char*)malloc(m*sizeof(char));
    }
    for(int i=0;i<n;i++){
        getchar();
        for(int j=0;j<m;j++){
            scanf("%c",&a[i][j]);
        }
    }
    int q;
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        int x,y,step;
        scanf("%d %d %d",&x,&y,&step);
        process(a[x-1][y-1],x-1,y-1,step);
    }
}