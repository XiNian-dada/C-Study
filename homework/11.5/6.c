#include <stdio.h>
#define d double
/*
 * 题目描述：计算交错级数和
 *
 * 输入：
 * - 一行: 一个正整数n (1 ≤ n ≤ 1000)
 *
 * 输出：
 * - 一行: 一个浮点数S，表示级数和，保留4位小数（四舍五入）
 *
 * 要求：
 * - 计算交错级数 S = a1 + a2 + a3 + ... + an
 * - 其中 ak = ± [1/(1·k) + 1/(2·k) + ... + 1/(k·k)]
 * - 符号正负交替，首项a1为正
 * - 结果保留4位小数
 *
 * 示例：
 * 输入: 1
 * 输出: 1.0000
 * 解释: a1 = 1/(1*1) = 1.0
 *
 * 输入: 3
 * 输出: 0.8611
 * 解释: S = a1 + a2 + a3 = 1 - (1/2 + 1/4) + (1/3 + 1/6 + 1/9) ≈ 0.8611
 *
 * 约束：
 * - 1 ≤ n ≤ 1000
 */
d math(int input){
    d temp = 0;
    for (int i = 1 ; i <= input ; i++){
        temp += 1.0 / (input * i); //计算级数
        
    }
    return (input % 2 == 0)?-temp : temp; //偶数项取反

}
int main(){ 

    int n;
    d sum = 0.0000;
    scanf("%d", &n);
    for (int i = 1 ; i <= n ; i++){
        sum += math(i);
    }
    
    printf("%.4f", sum);

}