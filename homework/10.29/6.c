#include <stdio.h>
/*
 * 题目描述：任意整数的各位数字之和
 * 
 * 输入：
 * - 一个32位带符号整数n
 * 
 * 输出：
 * - 一个整数，表示n的各位数字之和（忽略符号）
 * 
 * 要求：
 * - 计算整数的各位数字之和
 * - 忽略数字的符号（取绝对值）
 * - 输出为整数
 * 
 * 示例：
 * 输入: 1234
 * 输出: 10
 * 解释: 1 + 2 + 3 + 4 = 10
 * 
 * 输入: -12
 * 输出: 3
 * 解释: 取绝对值为12，1 + 2 = 3
 * 
 * 约束：
 * - n为32位带符号整数
 * - 需要考虑负数情况（取绝对值）
 */
int main() {
    //处理输入
    int input;
    int pos[100000];
    int i = 0;
    int sum = 0;
    scanf ("%d", &input);
    if (input == 0) {
        printf("0");
        return 0;
    }
    //取正，应该abs也可以
    input = (input > 0)? (input) : (-input);
    //只要Input !=0就执行，逐位取数，保存到pos数组里
    while (input != 0){
        
        pos[i] = input % 10;
        input /= 10;
        i++;
    }
    //计算每个位数的和
    for (int j = 0; j <i; j++){
        sum += pos[j];
    }
    printf("%d", sum);
}