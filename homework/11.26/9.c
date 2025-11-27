#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
/*
 * 题目描述：比较两个整数大小
 * 
 * 难度：中等-
 * 
 * 输入：
 * - 第1行：整数n，表示测试用例组数
 * - 随后n行：每行两个字符串，表示要比较的整数
 * 
 * 输出：
 * - n行：每行一个字符串，表示较小的数，或"Input Error"
 * 
 * 要求：
 * - 输入整数必须满足：大于等于0，小于等于10^30
 * - 如果输入不满足条件（包含非数字字符、负数、超出范围），输出"Input Error"
 * - 比较两个合法整数的大小，输出较小的那个
 * 
 * 验证规则：
 * - 必须是纯数字字符串（不能有符号、字母等）
 * - 数值范围：0 ≤ num ≤ 10^30
 * - 比较时按大整数比较（字符串比较或数值比较）
 * 
 * 示例：
 * 输入:
 * 4
 * 1234567 12345678474537585686857572
 * a 2
 * -1 12
 * 12324 ab
 * 输出:
 * 1234567
 * Input Error
 * Input Error
 * Input Error
 * 
 * 解释:
 * 第1组：两个合法整数，1234567 < 12345678474537585686857572
 * 第2组：包含非数字字符'a'
 * 第3组：包含负号'-'
 * 第4组：包含非数字字符'ab'
 * 
 * 约束：
 * - 输入可能非常大（最大10^30），需要用字符串处理
 * - 需要严格验证输入格式和范围
 */
void high_accuracy_cmp(char* s1,char* s2){
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if(len1 > len2){
        for(int i = 0; i < len2; i++){
            printf("%c", s2[i]);
            
        }
        return;

    }else if(len1 < len2){
        for(int i = 0; i < len1; i++){
            printf("%c", s1[i]);
        }
        return;
    }
    int who_is_smaller = 0;
    if(len1 == len2){
        for(int i = 0; i < len1; i++){
            if(s1[i] > s2[i]){
                who_is_smaller = 2;
                break;
            }else if(s1[i] < s2[i]){
                who_is_smaller = 1;
                break;
            }

        }
        if(who_is_smaller == 1){
            for(int i = 0; i < len1; i++){
                printf("%c", s1[i]);
            }
        }else if(who_is_smaller == 2){
            for(int i = 0; i < len2; i++){
                printf("%c", s2[i]);
            }
        }
    }

}
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        char s1[50],s2[50];
        memset(s1, '\0', sizeof(s1));
        memset(s2, '\0', sizeof(s2));
        scanf("%s %s", s1, s2);
        int len1 = strlen(s1);
        int len2 = strlen(s2);
        int founded = 0;
        for(int j = 0; j < len1; j++){
            if(!isdigit(s1[j])){
                printf("Input Error\n");
                founded = 1;
                break;
            }
        }
        if(founded == 0){
            for(int j = 0; j < len2; j++){
                if(!isdigit(s2[j])){
                    printf("Input Error\n");
                    founded = 1;
                    break;
                }
            }
        }
        if(founded == 0){
            high_accuracy_cmp(s1, s2);
            printf("\n");
        }
        
        

    }
}
