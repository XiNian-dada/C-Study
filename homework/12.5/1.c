#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "ctype.h"
#define ll long long
int input[50];
/*
 * 题目描述：学号转换
 * 
 * 难度：简单
 * 
 * 输入：
 * - 第1行：整数k，表示初始学号的进制（2 ≤ k ≤ 16）
 * - 第2行：字符串x，表示k进制下的学号
 * - 第3行：整数q，表示目标进制（2 ≤ q ≤ 16）
 * 
 * 输出：
 * - 一行字符串：表示q进制下的学号x
 * 
 * 要求：
 * - 将k进制数x转换为q进制数
 * - 如果进制大于10，使用大写字母A-F表示数字10-15
 *   A=10, B=11, C=12, D=13, E=14, F=15
 * - 转换过程：先将k进制数转换为10进制数，再将10进制数转换为q进制数
 * 
 * 转换规则：
 * 1. k进制转10进制：
 *    从高位到低位，每位的值×k^{位置权重}，然后求和
 *    例如：k进制数"134B4F7"（16进制）转10进制：
 *    1×16^6 + 3×16^5 + 4×16^4 + 11×16^3 + 4×16^2 + 15×16^1 + 7×16^0
 *    （B=11, F=15）
 * 
 * 2. 10进制转q进制：
 *    除q取余法，逆序排列
 *    例如：20231415（10进制）转16进制：
 *    20231415 ÷ 16 = 1264463 余 7  → 个位
 *    1264463 ÷ 16 = 79028 余 15 → F
 *    依次计算，逆序得到"134B4F7"
 * 
 * 示例1：
 * 输入:
 * 16
 * 134B4F7
 * 10
 * 输出:
 * 20231415
 * 
 * 解释:
 * 16进制"134B4F7"转10进制：
 * 1×16^6=16777216
 * 3×16^5=3145728
 * 4×16^4=262144
 * B(11)×16^3=45056
 * 4×16^2=1024
 * F(15)×16^1=240
 * 7×16^0=7
 * 总和：16777216+3145728+262144+45056+1024+240+7=20231415
 * 
 * 示例2：
 * 输入:
 * 7
 * 206636142
 * 13
 * 输出:
 * 2733447
 * 
 * 约束：
 * - 2 ≤ k, q ≤ 16
 * - 学号x转换为10进制后在int范围内
 * - 输入保证合法（不会出现超过进制范围的字符）
 * - 需要处理空字符串情况（虽然题目保证有输入）
 * 
 * 注意：
 * - 如果转换结果是0，应输出"0"
 * - 转换后的q进制数不应有前导0（除非数字本身就是0）
 * - 注意字母的大小写：必须使用大写A-F
 */
ll process_into_ten(int ori_jz, char* ori_str){
    ll result = 0;
    int len = strlen(ori_str);
    
    for(int i = 0; i < len; i++){
        int digit;
        if(isdigit(ori_str[i])){
            digit = ori_str[i] - '0';
        } else {
            digit = toupper(ori_str[i]) - 'A' + 10;
        }
        result = result * ori_jz + digit;
    }
    
    return result;
}
void trans_to_x_jz(ll sum,ll jz){
    char temp [50];
    int index;
    memset(temp, '\0', sizeof(temp));
    while(sum > 0){
        int digit = sum % jz;
        if(digit < 10){
            temp[index++] = digit+'0';
        } else {
            temp[index++] = digit-10+'A';
        }
        sum /= jz;
    }
    for(int i = index-1; i >= 0; i--){
        printf("%c", temp[i]);

    }
}
int main(){
    int input_jz;
    memset(input, -1, sizeof(input));
    char input_ori[50];
    memset(input_ori, '\0', sizeof(input_ori));
    int output_jz;
    scanf("%d", &input_jz);
    scanf("%s", input_ori);
    scanf("%d", &output_jz);
    ll sum = process_into_ten(input_jz, input_ori);
    trans_to_x_jz(sum, output_jz);
}
