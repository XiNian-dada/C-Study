#include <stdio.h>
/*
 * 题目描述：最大公约数
 * 
 * 输入：
 * - 第1行: 整数T, 表示测试数据的组数
 * - 随后T行: 每行包含两个正整数m和n，以空格隔开
 * 
 * 输出：
 * - T行: 每行一个整数，表示m和n的最大公约数
 * 
 * 要求：
 * - 计算两个正整数的最大公约数
 * - 每组输出占一行
 * 
 * 示例：
 * 输入: 
 * 3
 * 2 5
 * 4 6
 * 3 9
 * 输出:
 * 1
 * 2
 * 3
 * 
 * 解释:
 * 2和5的最大公约数是1
 * 4和6的最大公约数是2
 * 3和9的最大公约数是3
 * 
 * 约束：
 * - 输入为正整数
 */
int minus(int bigger, int smaller){ //相减法 国产的喵
    if(smaller * 2 == bigger){
        return smaller;
    }
    else{
        int max = smaller > (bigger - smaller) ? smaller : bigger - smaller;
        int min = smaller < (bigger - smaller) ? smaller : bigger - smaller;
        return minus(max,min);
    }
}

int main(){
    int n;
    int answer[100];
    scanf("%d", &n);
    
    int a,b;
    for (int i = 0; i < n; i++){
        scanf("%d %d", &a, &b);
        int max = a>b?a:b;
        int min = a>b?b:a;
        answer[i] = minus(max,min);
    }
    for (int i = 0; i < n; i++){
        printf("%d\n", answer[i]);
    }
}