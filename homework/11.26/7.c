#include "stdio.h"
#include "string.h"
#include "stdlib.h"
/*
 * 题目描述：子串跨度
 * 
 * 难度：中等
 * 
 * 输入：
 * - 一行：三个字符串S, S1, S2，以空格间隔
 * 
 * 输出：
 * - 一个整数：满足条件的最大跨距，不存在则输出-1
 * 
 * 要求：
 * - S1和S2都在S中出现
 * - S1位于S2的左边（S1的右边界在S2的左边界的左侧）
 * - S1和S2在S中互不交叉
 * - 计算最大跨距：最右边的S2的起始点与最左边的S1的终止点之间的字符数目
 * 
 * 跨距定义：
 * - 跨距 = (S2起始位置 - 1) - (S1结束位置) 
 * - 即S1结束位置到S2起始位置之间的字符个数（不包括S1和S2）
 * 
 * 示例：
 * 输入: "abcd123ab888efghij45ef67kl ab ef"
 * 输出: 18
 * 
 * 
 * 约束：
 * - S长度≤300，S1和S2长度≤10
 * - 字符串中不含空格
 */
int main(){
    char s[301],s1[11],s2[11];
    scanf("%s %s %s",s,s1,s2);
    char reverseS[301];
    int index = 0;
    for(int i=strlen(s)-1;i>=0;i--){
        reverseS[strlen(s)-1-i]=s[i];
        index++;
    }
    reverseS[index] = '\0';
    char reverseS2[11];
    
    
    index = 0;
    for(int i = strlen(s2) - 1; i >= 0; i--){
        reverseS2[strlen(s2) - 1 - i] = s2[i];
        index++;
    }
    reverseS2[index] = '\0';
    if (strstr(s,s1) == NULL || strstr(reverseS,reverseS2) == NULL){
        printf("-1\n");
        return 0;
    }
    int s1_pos = strstr(s,s1) - s;
    //printf("reverseS: '%s'\n", reverseS);
    //printf("reverseS2: '%s'\n", reverseS2);
    int s2_pos = strstr(reverseS,reverseS2) - reverseS;
    if(s1_pos > strlen(s) - s2_pos){
        printf("-1\n");
        return 0;
    }
    if(s1_pos + strlen(s1) >= strlen(s) - s2_pos + strlen(s2)){
        printf("-1\n");
        return 0;
    } 
    int py_len = strlen(s1) + strlen(s2);
    printf("%d\n",(strlen(s) - s2_pos) - py_len - s1_pos);
    //printf("%d %d %d",s1_pos,s2_pos,strlen(s));
}