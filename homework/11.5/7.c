#include <stdio.h>
#include <math.h>
/*
 * 题目描述：n的阶乘末尾有几个零
 *
 * 输入：
 * - 第1行: 整数n, 表示测试数据的组数
 * - 随后n行: 每行一个正整数m
 *
 * 输出：
 * - n行: 每行一个整数，表示m的阶乘结果末尾0的个数
 *
 * 要求：
 * - 计算m!末尾的连续零的个数
 * - 注意m!可能非常大，不能直接计算，需通过数学方法（统计因子5的个数）
 *
 * 示例：
 * 输入:
 * 2
 * 5
 * 100
 * 输出:
 * 1
 * 24
 *
 * 解释:
 * 5! = 120，末尾有1个0
 * 100! 末尾有24个0
 *
 * 约束：
 * - m为整数
 * - 结果可能很大，不能直接计算阶乘
 */
int how_many_five(int n){
    int count = 0;
    count = n / 5 + n / 25 + n / 125 + n / 625 + n / 3125; //计算5的因数的个数
    return count;
}
int main(){ 
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        int input;
        scanf("%d", &input);
        printf("%d\n", how_many_five(input));
    }

}