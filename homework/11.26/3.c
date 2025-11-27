#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/*
 * 题目描述：最长相同后缀
 * 
 * 输入：
 * - 两个非空字符串
 * 
 * 难度：简单+
 * 
 * 输出：
 * - 最长相同后缀字符串
 * - 如果不存在相同后缀，输出"null"
 * 
 * 要求：
 * - 从最后一个字符开始比较，找出最长的相等子串
 * - 相同后缀必须从字符串末尾开始连续匹配
 * 
 * 示例：
 * 输入: "abcdefg", "dadcefg"
 * 输出: "efg"
 * 
 * 输入: "abcdefg", "1234567" 
 * 输出: "null"
 * 
 * 解释:
 * 第一组：两个字符串都以"efg"结尾
 * 第二组：没有相同的后缀字符
 * 
 * 算法思路：
 * - 从两个字符串的末尾开始向前比较
 * - 记录连续匹配的字符数量
 * - 根据匹配数量提取后缀子串
 * 
 * 约束：
 * - 输入字符串非空
 * - 注意处理无相同后缀的情况
 */
int main(){
    char a[1000],b[1000];
    fgets(a,1000,stdin);
    fgets(b,1000,stdin);
    a[strcspn(a, "\n")] = '\0';
    b[strcspn(b, "\n")] = '\0';
    int a_len = strlen(a);
    int b_len = strlen(b);

    char* reverse_a = (char*)malloc(a_len*sizeof(char));
    char* reverse_b = (char*)malloc(b_len*sizeof(char));
    for(int i = 0; i < a_len; i++){
        reverse_a[i] = a[a_len-i-1];
    }
    for(int i = 0; i < b_len; i++){
        reverse_b[i] = b[b_len-i-1];
    }
    int min = a_len < b_len ? a_len : b_len;
    char lafix[1000];
    int founded = 0;
    int same_len = 0;
    for(int i = 0; i < min; i++){
        if(reverse_a[i] == reverse_b[i]){
            lafix[same_len] = reverse_a[i];
            same_len++;
            founded = 1;
        }else{
            break;
        }
    }
    
    if(founded == 1){
        for(int i = same_len-1; i >= 0; i--){
            printf("%c", lafix[i]);
        }
    }else{
        printf("null\n");

    }

}