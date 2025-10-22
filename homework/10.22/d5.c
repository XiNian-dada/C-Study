/*5: 两个圆的位置关系
描述
输入一行 6 个整数：x1 y1 r1 x2 y2 r2
表示圆 C1(x1,y1,r1) 与圆 C2(x2,y2,r2)，半径均>0。
按圆心距d与半径关系输出一个整数表示两个圆的位置关系：
0 相离 1 外切 2 相交 3 内切 4 内含 5 同心

输入
一行 6 个 int，空格分隔。

输出
0–5 之间的整数。*/
#include <stdio.h>
#include <math.h>
int main(){
    int x1,y1,r1,x2,y2,r2;
    scanf ("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
    double center_distance_squared = pow(x2-x1,2)+pow(y2-y1,2);
    double center_distance= sqrt(center_distance_squared);
    if (x1 == x2 && y1 == y2){
        printf("5");
    }else if (center_distance>r1+r2){
        printf("0");
    } else if (center_distance_squared == pow(r1+r2,2)){

        printf("1");
    } else if (center_distance<r1+r2 && center_distance> fabs(r1 - r2)){
        printf("2");
    } else if (center_distance_squared == pow(r1 - r2,2)){
        printf("3");
    } else if (center_distance<fabs(r1 - r2)){
        printf("4");
    } 
    return 0;
}