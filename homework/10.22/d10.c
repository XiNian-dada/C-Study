/*
10: 奇数的和
描述
输入2个整数m,n（0<m,n<1000)，计算mn之间的所有奇数的和。

输入
第1行是一个整数x，表示随后有x组数据。每组数据占一行，输入的整数用空格隔开。

输出
对每组数据，输出mn之间的所有奇数的和，并换行

样例
输入
2
1 6
14 8

输出
9
33
*/
#include <stdio.h>

int main(){
    int x,m[100000],n[100000];
    scanf ("%d", &x);
    for (int i = 0; i < x; i++){
        scanf ("%d %d", &m[i],&n[i]);
    }
    for (int i = 0; i < x; i++){
        int max,min;
        if (m[i]>n[i]){
            max = m[i];
            min = n[i];
        } else {
            max = n[i];
            min = m[i];
        }
        
        if (min %2 ==0){
            min++;
            int temp = 0;
            for (int j = min; j <= max; j+=2){

                temp += j;
            }
            printf("%d\n", temp);
        } else {
            int temp = 0;
            for (int j = min; j <= max; j+=2){
                temp += j;
            }
            printf("%d\n", temp);
        }
        
    }
    
}