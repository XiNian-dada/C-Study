/*
3. P1928 外星密码（可能有点难）
https://www.luogu.com.cn/problem/P1928
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[10000];  // 存储输入的密码字符串
int pos = 0;    // 当前处理的位置

/**
 * 递归解压缩函数
 * 返回当前层级解压后的字符串
 */
void decompress() {
    // 当没有到达字符串末尾时继续处理
    while (s[pos] != '\0') {
        // 如果遇到 ']' 说明当前层级结束，返回上一层
        if (s[pos] == ']') {
            pos++;  // 跳过 ']'
            return;
        }
        
        // 如果遇到 '[' 说明有压缩内容需要处理
        if (s[pos] == '[') {
            pos++;  // 跳过 '['
            
            // 提取重复次数 D（可能是多位数）
            int repeat = 0;
            while (s[pos] >= '0' && s[pos] <= '9') {
                repeat = repeat * 10 + (s[pos] - '0');
                pos++;
            }
            
            // 保存当前位置，以便重复多次
            int saved_pos = pos;
            
            // 重复解压指定次数
            for (int i = 0; i < repeat; i++) {
                pos = saved_pos;  // 每次都从 '[' 后面的内容开始处理
                decompress();     // 递归处理括号内的内容
            }
        } 
        // 如果是普通字符（字母），直接输出
        else {
            putchar(s[pos]);
            pos++;
        }
    }
}

int main() {
    // 读取输入的密码字符串
    scanf("%s", s);
    
    // 从位置0开始解压缩
    pos = 0;
    decompress();
    
    // 输出换行符
    printf("\n");
    
    return 0;
}