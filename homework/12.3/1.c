#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/*
 * 题目描述：子序列个数
 * 
 * 难度：中等-
 * 
 * 输入：
 * - 第1行：字符串str1，表示主字符串
 * - 第2行：字符串str2，表示子字符串
 * 
 * 输出：
 * - 一行整数：str1中包含str2的个数（允许重叠）
 * 
 * 要求：
 * - 计算str1中包含多少个str2子序列
 * - 子序列允许重叠计数
 * - 统计所有可能的位置匹配
 * 
 * 示例1：
 * 输入:
 * 01101010101
 * 1010
 * 输出: 3
 * 
 * 解释:
 * str1 = "01101010101", str2 = "1010"
 * 匹配位置：
 * 1. 位置1-4: "1010" (01101010101)
 * 2. 位置4-7: "1010" (01101010101)  
 * 3. 位置6-9: "1010" (01101010101)
 * 共3个匹配，允许重叠
 * 
 * 示例2：
 * 输入:
 * ababababac
 * abab
 * 输出: 3
 * 
 * 解释:
 * str1 = "ababababac", str2 = "abab"
 * 匹配位置：
 * 1. 位置0-3: "abab" (ababababac)
 * 2. 位置2-5: "abab" (ababababac)
 * 3. 位置4-7: "abab" (ababababac)
 * 共3个匹配，允许重叠
 * 
 * 约束：
 * - 输入为两个字符串，各占一行
 * - 字符串可能包含数字和小写字母
 * - 需要处理str2长度大于str1的情况（输出0）
 * - 匹配时区分大小写
 * - 需要去除输入字符串末尾的换行符
 */
int main(){
    char str1[1000];
    char str2[1000];
    scanf("%s", str1);
    getchar();
    scanf("%s", str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int pos = 0;
    int sum = 0;
    while(pos < len1){
        char temp[1000];
        memset(temp, '\0', sizeof(temp));
        for(int i = pos,j=0; i < len1; temp[j]=str1[i],i++,j++);
        if(strstr(temp, str2)!=NULL){
            sum++;
        }
        if(strstr(temp, str2)==NULL)break;
        pos+= strstr(temp, str2) - temp +1;
    }
    printf("%d", sum);
}

