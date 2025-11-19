#include "stdio.h"
/*
 * 题目描述：统计字符串中的数字个数
 * 
 * 输入：
 * - 第1行：整数n，表示测试数据的组数
 * - 随后n行：每行一个字符串
 * 
 * 输出：
 * - n行：每行一个整数，表示该字符串中连续数字段的个数
 * 
 * 要求：
 * - 统计字符串中连续数字序列的个数
 * - 连续的数字算作一个数字（如"123"算1个数字）
 * - 只要遇到非数字字符就结束当前数字计数
 * 
 * 示例：
 * 输入:
 * 2
 * 23frw90ewe3**325%
 * 45dsfafag2
 * 输出:
 * 4
 * 2
 * 
 * 解释:
 * 第一个字符串："23"、"90"、"3"、"325" → 共4个数字
 * 第二个字符串："45"、"2" → 共2个数字
 * 
 * 算法思路：
 * - 遍历字符串，使用状态标记是否正在读取数字
 * - 遇到数字字符时，如果前一个字符不是数字，则数字计数加1
 * - 遇到非数字字符时，结束当前数字读取状态
 * 
 * 约束：
 * - 字符串可能包含任意字符
 * - 连续的数字序列算作一个数字
 */
void process(){ 
    char c;
    int index = 0;
    char str[1000];
    while((c = getchar()) != '\n'){
        str[index++] = c;
    }
    int last_number=1;
    int count = 0;
    while(index--){
        if(str[index] >= '0' && str[index] <= '9'){
            last_number = 0;
            continue;
        }
        if(last_number == 0 && (str[index] < '0' || str[index] > '9'))
        {
            last_number = 1;
            count++;
            continue;
        }
        
    }
    if(last_number == 0){
        count++;
    }
    printf("%d\n", count);

}
int main(){
    int n;
    scanf("%d", &n);
    getchar();
    for(int i = 0; i < n; i++){
        process();
    }
}