#include "stdio.h"
#include "string.h"
#include "stdlib.h"
/*
 * 题目描述：字符串操作员
 * 
 * 输入：
 * - 第1行：初始字符串S（长度≤32，可能包含空格）
 * - 随后若干行：每行包含指令串和整数k，以空格分隔
 * - 以"End"结束输入
 * 
 * 难度：中等+
 * 
 * 输出：
 * - 对每组指令：输出执行指令后字符串的第k个字符（从1开始）
 * - 如果位置k不存在，输出"NULL"
 * - 每组指令在原始字符串上独立操作
 * 
 * 指令说明：
 * - L：字符串膨胀2倍，如"abc"→"aabbcc"
 * - R：字符串翻转，如"abc"→"cba"  
 * - Dn：删除中心左侧n个字母（n为整数）
 *     如果字符数不够，删除左侧全部字符
 *     例：D1："abcde"→"acde"，D2："abcde"→"cde"
 *         D1："abcd"→"acd"，D3："abcd"→"cd"
 * 
 * 示例：
 * 输入:
 * abcd
 * RD2L 3
 * D3R 20
 * End
 * 输出:
 * a
 * NULL
 * 
 * 解释:
 * 第一条指令：abcd → R→dcba → D2→ba → L→bbaa → 第3个字符是a
 * 第二条指令：abcd → D3→cd → R→dc → 没有第20个字符→NULL
 * 
 * 约束：
 * - 初始字符串长度≤32
 * - 指令串长度≤16
 * - 执行过程中字符串长度≤1000
 * - 每组指令在原始字符串上独立操作
 * - 需要处理可能包含空格的字符串
 */
void cmd_process(char* cmd,int cmd_len,char* strcp, int position){
    char* temp = (char*) malloc(strlen(strcp)*sizeof(char)*2);
    strcpy(temp, strcp);
    for(int i = 0; i < cmd_len; i++){
        switch(cmd[i]){
            case 'R':{
                char* temp2 = (char*)malloc(strlen(temp)*sizeof(char)*2+sizeof(char));
                for(int j = 0; j < strlen(temp); j++){
                    temp2[j] = temp[strlen(temp)-j-1];
                }
                temp2[strlen(temp)] = '\0';
                free(temp);
                temp = temp2;
                break;
            }
            case 'L':{
                char* temp2 = (char*)malloc(strlen(temp)*sizeof(char)*2 + sizeof(char));
                for(int j = 0;j < strlen(temp); j++){

                    temp2[j*2] = temp[j];
                    temp2[j*2+1] = temp[j];
                }
                temp2[strlen(temp)*2] = '\0';
                free(temp);
                temp = temp2;
                break;
            }
            case 'D': {
                i++; 
                int num = 0;
                while (i < cmd_len && cmd[i] >= '0' && cmd[i] <= '9') {
                    num = num * 10 + (cmd[i] - '0');
                    i++;
                }
                i-=1;
                
                int len = strlen(temp);
                int mid_pos = len / 2;
                int start_pos = (mid_pos - num < 0) ? 0 : (mid_pos - num);
                int delete_count = mid_pos - start_pos;
                
                char* temp2 = (char*)malloc((len - delete_count + 1) * sizeof(char));
                int index = 0;
                for(int j = 0; j < len; j++) {
                    if(j < start_pos || j >= mid_pos) {
                        temp2[index++] = temp[j];
                    }
                }
                temp2[index] = '\0';
                free(temp);
                temp = temp2;
                break;
            }
        }
    }
    int pos = position;
    int final_len = strlen(temp);
    if(pos > final_len){
        printf("NULL\n");
    }else{
        printf("%c\n", temp[pos-1]);
    }
    free(temp);

}
void process(char* str, char* scan, int output_num, int str_len, int scan_len){
    char* temp = (char*)malloc(str_len*sizeof(char));
    strcpy(temp, str);
    char command[16];
    for(int i = 0; i < scan_len; i++) command[i] = scan[i];
    int cmd_len = strlen(command);
    cmd_process(command,cmd_len,temp,output_num);
}


int main(){
    char str[1001];
    fgets(str, 1001, stdin);
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    int str_len = strlen(str);
    char scan[16][100];
    int i = 0,output_num[16];
    memset(output_num, 0, sizeof(output_num));
    while(i< 16){
        if(scanf("%s", scan[i]) != 1) break;
        
        if(strcmp(scan[i], "End") == 0) break;
        if(scanf("%d", &output_num[i]) != 1) {
            break;
        }
        i++;
    }
    int j = 0;
    while(j<i){
        process(str, scan[j], output_num[j],str_len,strlen(scan[j]));
        j++;

    }
}