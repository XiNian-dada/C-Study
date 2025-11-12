#include "stdio.h"
#include "stdlib.h"
/*
 * 题目描述：找出丢失的数
 * 
 * 输入：
 * - 第1行: 整数m, 表示测试数据的组数
 * - 随后m行: 每行包含n个正整数，以0结尾（0表示结束，不参与计算）
 * 
 * 输出：
 * - m行: 每行一个整数，表示1到n中缺失的那个数
 * 
 * 要求：
 * - 输入数据由1,2,3,...,n共n-1个数组成，缺失一个数k
 * - 找出缺失的数k
 * - 每组数据以0作为结束标志
 * 
 * 示例：
 * 输入:
 * 2
 * 2 3 1 5 0
 * 1 2 6 4 5 7 0
 * 输出:
 * 4
 * 3
 * 
 * 解释:
 * 第一组: 数字1,2,3,5，缺失4
 * 第二组: 数字1,2,4,5,6,7，缺失3
 * 
 * 约束：
 * - n ≤ 1000
 * - 每组数据以0结尾
 * - 保证有且仅有一个数缺失
 */
int main(){
    int n, a[1001] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        int input,index = 0;
        while(1){
            scanf("%d", &input);
            if(input != 0){
                a[index] = input;
                index++;
            }else{
                break;
            }
        }
        
        if(index == 0){
            printf("1\n");
            continue;
        }
        int num = 1;
        int len = index;
        for(int j = 0; j < len; j++){
            for(int k = 0; k < len; k++){
                if(num == a[k]){
                    num++;
                }
            }
        }
        printf("%d\n", num);
    }

}
