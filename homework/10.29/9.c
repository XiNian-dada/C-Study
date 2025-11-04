#include <stdio.h>
/*
 * 题目描述：数字变换（数字根计算）
 * 
 * 输入：
 * - 一个32位带符号正整数n (n > 0)
 * 
 * 输出：
 * - 一个整数，表示n的数字根（最终得到的一位数）
 * 
 * 要求：
 * - 不断重复以下步骤直到n变为一位数：
 *   1. 将n的各位数字相加得到新整数
 *   2. 用新整数替换原来的n
 * - 输出最终的一位数
 * 
 * 处理过程：
 * 重复计算各位数字之和，直到结果为一位数
 * 
 * 示例：
 * 输入: 9875
 * 输出: 2
 * 解释: 9875 → 9+8+7+5=29 → 2+9=11 → 1+1=2
 * 
 * 输入: 7
 * 输出: 7
 * 解释: 已经是一位数，直接输出
 * 
 * 约束：
 * - n为32位带符号正整数 (n > 0)
 * - 最终结果保证为1-9的一位数
 */
int devide_number(int a){//定义函数，入参为一个int
    //定义一个数组，保存各个位数
    int temp[100];
    int i =0;
    //如果输入小于10，那就是个位数，直接返回a
    if (a < 10){
        return a;
    }
    //反之，开始取位保存到数组temp里，并开始求和
    //再返回 devide_number(sum)
    if (a >= 10){
        while (a > 0){
            temp[i] = a%10;
            a = a/10;
            i++;
        }
        int sum = 0;
        for (int j = 0; j < i; j++){
            sum += temp[j];
        }
        return devide_number(sum);
    }
    
}
int digital_root(int n) {return (n - 1) % 9 + 1;} //公式法，逆天吧
int main(){
    int input;
    scanf("%d", &input);
    printf("%d",(input - 1) % 9 + 1);
    printf("%d", digital_root(input));
    printf("%d", devide_number(input));
}

