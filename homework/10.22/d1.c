/*
1: 最大值和最小值的差
描述
输入 3 个十进制整数，计算最大值和最小值的差并输出。

输入
输入 3 个十进制整数，范围是−100∼100，中间以空格分隔。

输出
输出最大值和最小值的差。
*/
#include <stdio.h>
int main(){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    int max,min;
    if (a>b){
        max = a;
        min = b;
    }else {
        max = b;
        min = a;
    }
    
    if (c>max) max =c;
    if (c<min) min =c;
    printf("%d\n",max-min);
    


}