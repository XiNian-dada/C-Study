#include "stdio.h"
#include "stdlib.h"
/*
 * 题目描述：回文数判断
 * 
 * 难度：简单
 * 
 * 输入：
 * - 第1行：正整数n，表示数据组数
 * - 随后n行：每行一个正整数m
 * 
 * 输出：
 * - n行：对每个m，如果是回文数输出"Yes"，否则输出"No"
 * 
 * 要求：
 * - 回文数定义：十进制表示下，顺序和逆序相同的整数
 * - 例如：1234321、123321等都是回文数
 * 
 * 示例：
 * 输入:
 * 3
 * 1231
 * 12321
 * 12345
 * 输出:
 * No
 * Yes
 * No
 * 
 * 解释:
 * 1231 → 逆序1321，不相同 → No
 * 12321 → 逆序12321，相同 → Yes  
 * 12345 → 逆序54321，不相同 → No
 * 
 * 约束：
 * - 输入正整数在32位int范围内
 * - 需要处理多组测试数据
 */
void reverse(int input){
    int reverse_num = 0;
    int input_copy = input;
    while(input > 0){
        reverse_num = reverse_num * 10 + input % 10;
        input /= 10;
    }
    if(reverse_num == input_copy){
        printf("Yes\n");
    }else{
        printf("No\n");
    }

}

int main(){
    int n;
    scanf("%d", &n);
    int *list;
    list = (int*)malloc(n*sizeof(int));
    for(int i=0; i<n; i++){
        scanf("%d", &list[i]);
    }
    for(int i=0; i<n; i++){
        reverse(list[i]);
    }

}
