#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
 * 题目描述：计算平均值（二）
 * 
 * 难度：简单+
 * 
 * 输入：
 * - 第1行：整数n (1 ≤ n ≤ 100)，表示数据个数
 * - 第2行：n个数据，用空格分隔，可能包含整数或"n/a"
 * 
 * 输出：
 * - 一行：有效整数的平均值，保留小数点后两位
 * - 如果所有数据都是"n/a"，则输出"n/a"
 * 
 * 要求：
 * - 计算平均值时排除无效整数（"n/a"）
 * - 只对有效整数计算平均值
 * - 结果保留两位小数
 * - 如果所有输入都是"n/a"，输出"n/a"
 * 
 * 示例：
 * 输入:
 * 6
 * 1 2 3 n/a 5 6
 * 输出: 3.40
 * 
 * 解释:
 * 有效整数：1, 2, 3, 5, 6
 * 平均值 = (1+2+3+5+6)/5 = 17/5 = 3.40
 * 
 * 约束：
 * - 1 ≤ n ≤ 100
 * - 需要区分整数和字符串"n/a"
 * - 注意处理全为"n/a"的情况
 */
int main(){
    int n;
    scanf("%d",&n);
    getchar();
    char s[1000];
    fgets(s,1000,stdin);
    s[strcspn(s, "\n")] = '\0';

    int len = strlen(s);
    int sum = 0;
    int num_founded = 0;

    char* token;
    token = strtok(s," ");
    while(token != NULL){
        if(strcmp(token, "n/a") == 0){
            n--;
        }else{
            int num = atoi(token);
            sum += num;
            num_founded = 1;
        }
        token = strtok(NULL," ");
    }
    if(num_founded == 1){
        printf("%.2f", (float)sum/n);
    }else{
        printf("n/a");
    }
}
