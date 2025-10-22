/*
6: 判断字符类型
描述

输入一个字符，判断是哪类字符


输入

第1行是一个整数n，表示随后有n组数据。
每组数据占一行，包含一个字符。


输出

对于每一组数据，
若该字符是数字，则输出“number”；
若该字符是字母，则输出“letter”
否则输出“else”。


样例

输入
1 a +

输出
number letter else
*/

#include <stdio.h>

int main(){
    int n;
    char input[100000];
    scanf ("%d\n", &n);
    for (int i = 0; i < n; i++){
        scanf ("%c\n", &input[i]);
    }
    for (int i = 0; i < n; i++){
        if (input[i] >= 'a' && input[i] <= 'z'){
            printf ("letter\n");
        }else if (input[i] >= 'A' && input[i] <= 'Z'){
            printf ("letter\n");
        }else if (input[i] >= '0' && input[i] <= '9'){
            printf ("number\n");
        }else{
            printf ("else\n");
        }
    }
}