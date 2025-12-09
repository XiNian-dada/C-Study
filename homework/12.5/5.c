#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
/*
 * 题目描述：海王自动转发机
 * 
 * 难度：简单+
 * 
 * 输入：
 * - 第1行：原始字符串c（长度不超过10000）
 * - 第2行：需要被替换的子串x（长度不超过10）
 * - 第3行：用于替换的字符串y（长度不超过1000）
 * 
 * 输出：
 * - 一行：将c中所有子串x替换为y后的新字符串
 * 
 * 要求：
 * - 替换需要区分大小写
 * - 需要替换所有出现的子串x（包括可能重叠的部分）
 * - 替换规则：当发现匹配的子串x时，用y替换该子串，然后继续从替换后的位置向后查找
 * - 注意：替换后的字符串可能包含原x子串，但这些新出现的部分不应再次被替换
 * 
 * 重要规则说明：
 * 题目明确说明：若需要替换称呼为anan，c中字符串包含banananc，则只需要替换出现在第2-5个字符的第一个anan。
 * 这意味着：
 * 1. 替换是"非重叠"的：当找到一个匹配后，下一个查找从本次替换结束的位置开始
 * 2. 例如："banananc"中查找"anan"：
 *    - 位置2-5匹配"anan"（b[anan]anc）
 *    - 替换后继续从位置5（原位置5）之后开始查找，不会再次匹配重叠的部分
 * 3. 这与普通的字符串替换算法一致
 * 
 * 示例1：
 * 输入:
 * AnandoyouthinkthattalkingtoAnanaboutthingsrelatedtoananisenough
 * Anan
 * Wangwang
 * 输出:
 * WangwangdoyouthinkthattalkingtoWangwangaboutthingsrelatedtoananisenough
 * 
 * 解释:
 * 原始字符串中有两个"Anan"（注意大小写）需要替换：
 * 1. 开头的"Anan" → "Wangwang"
 * 2. "talkingtoAnan"中的"Anan" → "Wangwang"
 * 末尾的"anan"不匹配（大小写不同），不替换
 * 
 * 示例2：
 * 输入:
 * ananabanana
 * ana
 * XYZ
 * 输出:
 * XYZbXYZna
 * 
 * 解释:
 * "ananabanana"中查找"ana"：
 * 1. 位置1-3："ana" → "XYZ"（ananabanana → XYZnabana）
 * 2. 继续从位置4开始查找："nabana"中位置2-4："ana" → "XYZ"（XYZnabana → XYZbXYZna）
 * 注意：替换后新字符串中的"XYZ"不会再次被匹配替换
 * 
 * 约束：
 * - 原始字符串c长度≤10000
 * - 被替换子串x长度≤10
 * - 替换字符串y长度≤1000
 * - 字符串只包含大小写英文字母
 * - 需要区分大小写
 * - 替换后的字符串长度可能变化，需要动态管理内存或使用足够大的缓冲区
 * 
 * 提示：
 * 1. 可以使用KMP算法或直接使用字符串库函数进行查找
 * 2. 由于x长度很短（≤10），直接使用暴力匹配也可以接受
 * 3. 需要动态构建新字符串，避免在原字符串上直接修改
 */
int main(){
    char input[10001];
    char th[1001];
    char ori[11];
    memset(ori, '\0', sizeof(ori));
    memset(th, '\0', sizeof(th));
    memset(input, '\0', sizeof(input));
    scanf("%s",input);
    scanf("%s",ori);
    scanf("%s",th);
    int s[10001],e[10001];
    memset(s, 0, sizeof(s));
    memset(e, 0, sizeof(e));
    while(strstr(input, ori) != NULL){
        int start_pos = strstr(input, ori) - input;
        int end_pos = start_pos + strlen(ori);
        s[start_pos] = 1;
        e[end_pos] = 1;
        for(int i = start_pos; i < end_pos; i++){
            input[i] = '-';
        }
    }
    for(int i = 0; i < strlen(input); i++){
        if(s[i] == 1){
            printf("%s", th);
            i += strlen(ori) - 1;
        }
        else{
            printf("%c", input[i]);
        }
    }
}

