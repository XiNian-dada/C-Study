/*

3: 计算分段函数
描述
输入实数 x，计算
x<0 时 y = x²
0≤x≤10 时 y = 2x+3
x>10 时 y = 3x-7
输出 y，保留 2 位小数。

输入
输入1个实数x，double类型。

输出
y，保留2位小数。

样例
输入
0

输出
3.00

输入
-2.4

输出
5.76
*/ 



#include <stdio.h>
int main(){
    double x;
    scanf("%lf", &x);
    if (x < 0){
        printf("%.2lf\n", x*x);
    } else if (0<=x && x<=10){
        printf("%.2lf\n", 2*x + 3.0);
    } else {
        printf("%.2lf\n", x*3 - 7.0);
    }
    
}