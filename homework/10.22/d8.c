/*
8: 平方根
描述
计算整数的平方根。

输入
第1行是一个整数n,表示随后有n组数据。每组数据占一行，包含一个整数
−10000≤m≤10000。

输出
对每组数据m，计算m的平方根，精确到小数点后2位。如果m没有平方根，则输出ERROR。

样例
输入
0 2 -1

输出
0.00
1.41
ERROR
*/
#include <stdio.h>
#include <math.h>

int main(){ 
    int n;
    int m[10000];
    scanf ("%d", &n);
    for (int i = 0; i < n; i++){
        scanf ("%d\n", &m[i]);
    }
    for (int i = 0; i < n; i++){
        if (m[i] < 0){
            printf("ERROR\n");
            continue;
        } else {
            printf("%.2f\n", sqrt(m[i]));
        }
    }
}
