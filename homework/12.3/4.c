#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
/*
 * 题目描述：单词逆序
 * 
 * 难度：中等-
 * 
 * 输入：
 * - 一行语句，长度不超过1000个字符
 * 
 * 输出：
 * - 一行：每个单词逆序后的语句，其他符号保持不变
 * 
 * 要求：
 * - 只对单词进行逆序，其他符号（标点、空格等）保持原位置不变
 * - 单词由字母组成（大小写字母）
 * - 非字母字符视为单词分隔符，保持原样
 * - 保持原有的大小写形式
 * 
 * 示例：
 * 输入:
 * I like thinking...
 * 输出:
 * I ekil gnikniht...
 * 
 * 解释:
 * "I" → 逆序为"I"（单个字符）
 * "like" → 逆序为"ekil"
 * "thinking..." → 其中"thinking"是单词，逆序为"gnikniht"，句点保持原位置
 * 
 * 其他示例：
 * 输入:
 * Hello, world!
 * 输出:
 * olleH, dlrow!
 * 
 * 输入:
 * a1b c2d e3f
 * 输出:
 * b1a d2c f3e
 * （数字视为单词的一部分）
 * 
 * 约束：
 * - 输入字符串长度≤1000
 * - 需要考虑多个连续分隔符的情况
 * - 需要处理开头和结尾的特殊字符
 */
int main(){
    char buff[1000];
    int i = 0;
    int ch;
    
    while((ch = getchar()) != EOF){
        if(isalpha(ch)){
            buff[i++] = ch;
        }
        else{
            for(int j = i-1; j >= 0; j--){
                putchar(buff[j]);
            }
            putchar(ch);
            i = 0;
        }
    }
    if(i > 0){
        for(int j = i-1; j >= 0; j--){
            putchar(buff[j]);
        }
    }
    
    return 0;
}