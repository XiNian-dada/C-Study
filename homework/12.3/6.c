#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
/*
 * 题目描述：找子串
 * 
 * 难度：中等
 * 
 * 输入：
 * - 第1行：待查找的字符串（长度不超过100）
 * - 第2行：要查找的子串（长度不超过100）
 * 
 * 输出：
 * - 如果找到子串：在每个匹配的子串前后加上注释符号，保持子串原样输出
 * - 如果没有找到：原样输出字符串
 * - 注意：查找不区分大小写，但输出时要保持原字符串的大小写
 * 
 * 要求：
 * - 子串查找不区分大小写（one、One、ONE视为相同）
 * - 子串不会重叠出现
 * - 需要在所有匹配位置添加注释
 * - 注释格式：在子串前加"/*"，在子串后加"*_/"，这里用_避免嵌套注释问题）
 * - 保持原字符串的字符大小写
 * 
 * 示例1：
 * 输入:
 * You are the best!
 * are
 * 输出:
 * You /*are*_/ the best!
 * 
 * 解释:
 * 在字符串中找到"are"（不区分大小写），在原位置添加注释
 * 
 * 示例2：
 * 输入:
 * You are the best!
 * E
 * 输出:
 * You ar/*e*_/ th/*e*_/ b/*e*_/st!
 * 
 * 解释:
 * 查找子串"E"（不区分大小写），找到所有'e'或'E'字符
 * 分别在位置4、10、13找到'e'，添加注释
 * 注意：输出保持原字符串的大小写
 * 
 * 示例3：
 * 输入:
 * Hello World
 * hello
 * 输出:
 * /*Hello*_/ World
 * 
 * 解释:
 * 不区分大小写，"Hello"匹配"hello"
 * 输出时保持原字符串的"H"大写
 * 
 * 约束：
 * - 输入字符串长度≤100
 * - 子串长度≤100
 * - 需要处理空字符串的情况
 * - 需要去除输入字符串末尾的换行符
 * - 子串不会重叠出现（简化处理逻辑）
 * 
 * 
 */
//注意：实际代码中注释符号应为/*和*/，这里用描述说明
int main(){
    char str1[200],str2[200];
    int start_flag_pos[200],end_flag_pos[200];
    int uppercase_pos[200];
    memset(start_flag_pos,0,sizeof(start_flag_pos));
    memset(end_flag_pos,0,sizeof(end_flag_pos));
    memset(uppercase_pos,0,sizeof(uppercase_pos));
    scanf("%[^\n]",str1);//全部改LOWERCASE方便判断，然后记录位置UPPERCASE
    getchar();
    scanf("%[^\n]",str2);
    for(int i =0;i<strlen(str1);i++){
        if(isupper(str1[i])){
            uppercase_pos[i] = 1;
            str1[i] = tolower(str1[i]);
        }
    }
    for(int i =0;i<strlen(str2);i++){
        str2[i] = tolower(str2[i]);
    }
    for(int i =0;i<strlen(str1)-strlen(str2)+1;i++){
        int founded = 0;
        for(int j =0;j<strlen(str2);j++){
            if(str1[i+j] != str2[j]){
                founded = 1;
                break;
            }
        }
        if(founded == 0){
            start_flag_pos[i] = 1;
            end_flag_pos[i+strlen(str2)-1] = 1;
        }
    }
    for(int i = 0;i<strlen(str1);i++){
        if(start_flag_pos[i] == 1){
            printf("/*");
        }
        if(uppercase_pos[i] == 1){
            printf("%c",str1[i] - 32);
        }else{
            printf("%c",str1[i]);
        }
        if(end_flag_pos[i] == 1){
            printf("*/");
        }
    }
}

