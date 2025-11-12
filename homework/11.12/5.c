#include "stdio.h"
/*
 * 题目描述：交换十进制整数的相邻奇偶位
 * 
 * 输入：
 * - 一个32位带符号整数n
 * 
 * 输出：
 * - 一个整数，表示交换相邻奇偶位后的结果
 * 
 * 要求：
 * - 将n的十进制表示中奇数位与偶数位数字交换
 * - 奇数位：从左往右数第1、3、5...位
 * - 偶数位：从左往右数第2、4、6...位
 * - 保持原符号不变
 * - 忽略前导零
 * 
 * 示例：
 * 输入: 1234
 * 输出: 2143
 * 解释: 奇数位(1,3)与偶数位(2,4)交换 → 2,1,4,3 → 2143
 * 
 * 输入: -123
 * 输出: -213
 * 解释: 取绝对值123 → 奇数位(1,3)与偶数位(2)交换 → 2,1,3 → 213 → 加符号-213
 * 
 * 约束：
 * - n为32位带符号整数
 * - 需要考虑负数的处理
 */
int first_process = 1;
int main(){
    int is_negative = 0;
    int input[11] = {-1};
    int index = 0;
    int n;
    scanf("%d",&n);
    if (n<0){
        n = -n;
        is_negative =1;
    }
    if (n == 0){
        printf("0");
        return 0;
    }
    while(1){
        if(n == 0){
            break;
        }
        
        input[index] = n%10;
        n = n/10;
        index++;
    }
    if(is_negative){
        printf("-");
    }
    if(index % 2 == 0){
        for (int i = index-1; i >= 0; i-=2){
            if(first_process && input[i-1] == 0){
                printf("%d",input[i]);
                first_process = 0;
            }else{
                printf("%d%d",input[i-1],input[i]);
            }
            
        }
    }else{
        for (int i = index-1; i >= 1; i-=2){
            if(first_process && input[i-1] == 0){
                printf("%d",input[i]);
                first_process = 0;
            }else{
                printf("%d%d",input[i-1],input[i]);
            }
        }
        printf("%d",input[0]);
    }
    
}