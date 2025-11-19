#include "stdio.h"
/*
 * 题目描述：N行直角杨辉三角
 * 
 * 输入：
 * - 一个不大于20的正整数n
 * 
 * 输出：
 * - 如果n不在1-20范围内，输出"Input Error"
 * - 否则输出n行直角杨辉三角，每行数字用英文逗号相隔
 * 
 * 要求：
 * - 杨辉三角规则：
 *   第1行：1
 *   第2行：1,1
 *   第i行：第一个和最后一个数为1，其余数 = 上方数 + 左上方数
 * - 输出格式：每行数字用英文逗号相隔，行末也有逗号
 * - 输出为直角形式（左对齐）
 * 
 * 示例：
 * 输入: 1
 * 输出: 1,
 * 
 * 输入: 4
 * 输出: 
 * 1,
 * 1,1,
 * 1,2,1,
 * 1,3,3,1,
 * 
 * 解释:
 * 第1行: 1
 * 第2行: 1,1  
 * 第3行: 1,2,1 (2=1+1)
 * 第4行: 1,3,3,1 (3=1+2, 3=2+1)
 * 
 * 约束：
 * - 1 ≤ n ≤ 20
 * - 注意输出格式：英文逗号分隔，行末有逗号
 * - 需要验证输入合法性
 */
int ass_triangle(int n){ 
    int list[21][21];
    for(int i = 0; i < 21; i++){
        for(int j = 0; j < 21; j++){
            list[i][j] = 0;
        }
    }
    list[0][0] = 1;
    list[1][0] = 1;
    list[1][1] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            if(j == 0){
                list[i][0] = 1;
                printf("%d,", list[i][j]);
                continue;
            }
            list[i][j] = list[i-1][j-1] + list[i-1][j];
            printf("%d,", list[i][j]);
        }
        printf("\n");
    }
}
int main(){
    int n;
    scanf("%d", &n);
    if(n > 20 || n <= 0){
        printf("Input Error");
        return 0;
    }
    ass_triangle(n);
    
    
}