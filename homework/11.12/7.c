#include "stdio.h"
/*
 * 题目描述：递归实现逆序输出字符串
 * 
 * 输入：
 * - 第1行: 整数n, 表示测试数据的组数
 * - 随后n行: 每行一个字符串
 * 
 * 输出：
 * - n行: 每行一个字符串，表示输入字符串的逆序
 * 
 * 要求：
 * - 必须使用递归函数实现字符串逆序输出
 * - 每组输出占一行
 * 
 * 示例：
 * 输入:
 * 3
 * abcd
 * 1234567
 * qwertyuiop
 * 输出:
 * dcba
 * 7654321
 * poiuytrewq
 * 
 * 约束：
 * - 必须使用递归实现
 * - 字符串长度未明确限制，但应合理处理
 */
void negative_output(char input){
    if(input == '\n'){
        return;
    }
    negative_output(getchar());
    putchar(input);

}
int main(){
    int n;
    scanf("%d",&n);
    getchar();
    char c;
    for (int i = 0; i < n; i++){
        c = getchar();
        negative_output(c);
        putchar('\n');
    }
    
}