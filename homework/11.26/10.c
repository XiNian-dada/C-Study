#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
char input[100][31];
/*
 * 题目描述：IP地址判断
 * 
 * 难度：困难-
 * 
 * 输入：
 * - 多行输入，每行一个字符串
 * - 以EOF（End of file）结束输入
 * 
 * 输出：
 * - 对每个字符串：如果是合法IPv4地址输出"YES"，否则输出"NO"
 * 
 * 要求：
 * - IPv4地址格式：A.B.C.D（4个部分由点分隔）
 * - 每个部分A,B,C,D都是[0,255]范围内的整数
 * - 不能有前导零（如001、01等）
 * - 必须是纯数字，不能包含其他字符
 * 
 * 验证规则：
 * 1. 必须恰好包含3个点分隔符
 * 2. 分隔的4个部分都必须是纯数字
 * 3. 每个数字不能有前导零（除非数字本身就是0）
 * 4. 每个数字在0-255范围内
 * 
 * 示例：
 * 输入:
 * 202.115.32.24
 * a.b.c.d
 * 输出:
 * YES
 * NO
 * 
 * 解释:
 * "202.115.32.24" → 4个合法数字 → YES
 * "a.b.c.d" → 包含非数字字符 → NO
 * 
 * 约束：
 * - 字符串长度≤30
 * - 不含空格和不可见字符
 * - 需要处理多行输入直到EOF
 */
int judge_ipv4(char* origin_ip,int len){
    int is_valid_number = 1;
    int dot_num = 0;
    char temp[31];
    strcpy(temp, origin_ip);
    temp[strcspn(temp, "\n")] = '\0';
    temp[strcspn(temp, " ")] = '\0';
    len = strlen(temp);
    if(len < 7) return 0;
    for(int i = 0; i < len; i++){
        if((isspace(temp[i])||ispunct(temp[i])) && temp[i] != '.' && temp[i] != '\n' && temp[i] != '\0') return 0;
    }
    if(temp[len-1] < '0' || temp[len-1] > '9'){
        is_valid_number = 0;
        return 0;
    }
    
    for(int i = 0; i < strlen(temp)-1; i++){
        if(temp[i] == '.' && temp[i+1] == '.'){
            is_valid_number = 0;
            return 0;
        }
    }
    for(int i = 0; i < strlen(temp); i++){
        if(temp[i] == '.') dot_num++;continue;
        if(temp[i] < '0' || temp[i] > '9')return 0;
    }
    if(dot_num != 3) return 0;
    for(int i = 0; i < strlen(temp); i++){
        if(isalpha(temp[i])) is_valid_number = 0;

    }
    char* token = strtok(temp, ".");
    int seg = 0;
    while(token != NULL){
        if(strlen(token) == 0) return 0;
        if(strlen(token) > 3) return 0;
        int num = atoi(token);
        if(num < 0 || num > 255) return 0;
        int token_len = strlen(token); 
        if (token_len > 1 && token[0] == '0') {
            return 0; 
        }
        seg++;
        token = strtok(NULL, ".");
    }
    if(seg != 4)return 0;
    if(is_valid_number == 1 && dot_num == 3){
        return 1;
    }else {return 0;}
}

int main(){
    int line = 0;
    while(1){
        fgets(input[line], 31, stdin);
        if (strstr(input[line], "End of file") != NULL) {
            break;  
        }
        line++;
    }
    for(int i = 0; i < line; i++){
        if(judge_ipv4(input[i],strlen(input[i])) == 1){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}