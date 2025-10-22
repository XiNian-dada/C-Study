/*
9: 三角形形状
描述
从键盘输入 a,b,c 三个整数，作为三角形的三条边长，判断这是一个直角/锐角/钝角三角形？

输入
第1行是一个整数 n，表示随后有 n 组数据。每组数据占一行，依次输入三个整数，分别表示
a,b,c，数字间用逗号隔开。

输出
如果是锐角三角形，输出字符串 acute
如果是直角三角形，输出字符串 right
如果是钝角三角形，输出字符串 obtuse
如果无法构成三角形，输出字符串 illegal

样例
输入
3
3,4,5
1,2,1
6,5,4

输出
right
illegal
acute
*/
#include <stdio.h>
#define ll long long
int main(){
    int n;
    int a[10000],b[10000],c[10000];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d,%d,%d", &a[i], &b[i], &c[i]);
    }
    

    for (int i = 0; i < n; i++){
        ll A = a[i]*a[i];
        ll B = b[i]*b[i];
        ll C = c[i]*c[i];
        if (a[i] + b[i] > c[i] && a[i] + c[i] > b[i] && b[i] + c[i] > a[i]){
            if(A + B == C || A + C == B || B + C == A){
                printf("right\n");
        
            } else if (A + B < C || A + C < B || B + C < A){
                printf("obtuse\n");
            }
            else {
                printf("acute\n");
            }
        } else {
            printf("illegal\n");
        }
    }
}