#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/*
 * 题目描述：大整数加法
 * 
 * 难度：中等-
 * 
 * 输入：
 * - 第1行：整数n，表示测试数据的组数
 * - 接下来n行：每行包含两个大整数a和b，用空格分隔
 * 
 * 输出：
 * - 对于每组测试数据，输出一行：a和b的和
 * 
 * 要求：
 * - 计算两个大整数的和
 * - 大整数可能非常大，无法用标准整数类型直接存储
 * 
 * 数据范围：
 * - 0 ≤ a, b ≤ 10^500（即a和b最多有501位数字）
 * - 这意味着：
 *   1. 不能用int、long long等类型直接存储
 *   2. 需要用字符串或数组来存储数字
 *   3. 需要手动实现加法运算
 * 
 * 大整数加法算法：
 * 1. 将两个数字字符串反转（从个位开始处理）
 * 2. 逐位相加，考虑进位
 * 3. 从最低位（个位）到最高位逐位计算
 * 4. 如果某一位相加结果≥10，则进位=1，当前位=结果-10
 * 5. 处理完所有位后，如果还有进位，需要增加一位
 * 6. 将结果反转回来得到正常顺序
 * 
 * 示例：
 * 输入:
 * 3
 * 1 2
 * 5 8
 * 1 999
 * 
 * 输出:
 * 3
 * 13
 * 1000
 * 
 * 解释第三组：
 * 1 + 999 = 1000
 * 从个位开始：1+9=10 → 写0进1
 * 十位：0+9+进位1=10 → 写0进1
 * 百位：0+9+进位1=10 → 写0进1
 * 千位：0+0+进位1=1 → 写1
 * 结果：1000（需要反转得到正确顺序）
 * 
 * 特殊情况：
 * 1. 输入可能包含前导零（如"00123"），可以处理或保留
 * 2. 结果为0时输出"0"
 * 3. 输入的两个数位数可能不同
 * 4. 最高位可能有进位
 * 
 * 约束：
 * - 1 ≤ n ≤ 100（合理假设）
 * - 每个数字长度≤501位（包括可能的前导零）
 * - 输入数字是非负整数
 * - 输出不应有前导零（除非结果为0）
 * 
 * 实现提示：
 * 1. 使用字符数组或字符串存储数字
 * 2. 可以用strlen获取数字长度
 * 3. 注意字符'0'到数字0的转换（减'0'）
 * 4. 注意数字0到字符'0'的转换（加'0'）
 */
typedef struct {
    int a[501];
    int len;
}big_num;
void trans_2_num(char* s,big_num* num){
    num->len = strlen(s);
    memset(num->a,0,sizeof(num->a));
    for(int i = 0;i<num->len;i++){
        num->a[i] = s[num->len-i-1]-'0';
    }
}
void add_num(big_num* a , big_num* b, big_num* result){
    int max_len = a->len > b->len ? a->len : b->len;
    int carry = 0;
    result->len = 0;
    for(int i = 0;i<max_len;i++){
        int temp = a->a[i] + b->a[i] + carry;
        result->a[i] = temp % 10;
        carry = temp / 10;
        result->len++;
    }
    if(carry){
        result->a[max_len] = carry;
        result->len++;
    }
}


int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        char s1[501],s2[501];
        memset(s1,'\0',sizeof(s1));
        memset(s2,'\0',sizeof(s2));
        scanf("%s %s",s1,s2);
        big_num num1,num2,result;
        trans_2_num(s1,&num1);
        trans_2_num(s2,&num2);
        add_num(&num1,&num2,&result);
        for(int i = result.len-1;i>=0;i--){
            printf("%d",result.a[i]);
        }
        printf("\n");

    }
}