#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "ctype.h"
#define ll long long
/*
 * 题目描述：统计回文数
 * 
 * 难度：中等+
 * 
 * 输入：
 * - 多行文本输入，直到文件末尾（EOF）
 * - 文本包含字母、数字、标点符号等字符
 * 
 * 输出：
 * - 输出出现次数最多的回文数及其出现次数
 * - 格式：每行一个，按"数字 次数"格式输出
 * - 如果有多个回文数出现次数相同且最多，按数字从小到大依次输出
 * - 如果没有找到任何回文数，输出"None"
 * 
 * 回文数定义：
 * 1. 十进制无符号整数
 * 2. 顺序和逆序相同（如12321、1221、11、99等）
 * 3. 长度至少为2位（即排除单个数字）
 * 4. 不能以0开始（即不能有前导零，如01210不合法）
 * 5. 不考虑负数和小数
 * 
 * 重要规则：
 * 1. 不考虑数的一部分：即必须在文本中作为完整的整数出现
 *   例如："abc1232abc"中的"232"不是一个单独的数（它是"1232"的一部分）
 * 2. 数字可能非常大，超过32位整数范围，因此需要按字符串处理
 * 3. 回文数必须是完整的整数，不是其他字符串的子串
 * 
 * 数字提取规则：
 * 1. 连续的数字字符组成一个整数
 * 2. 整数边界：非数字字符或字符串开头/结尾
 * 3. 例如："Thin34543king 121 is8 interesting121."
 *   提取的数字："34543"、"121"、"8"、"121"
 *   其中："8"长度<2，忽略；"34543"和"121"是有效回文数
 * 
 * 示例：
 * 输入:
 * Thin34543king 121 is8 interesting121.
 * I like121 thinking23.
 * 输出:
 * 121 3
 * 
 * 解释:
 * 提取的数字和检查：
 * 1. "34543"：长度5，回文，出现1次
 * 2. "121"：长度3，回文，出现3次
 * 3. "8"：长度1，忽略
 * 4. "121"：同上
 * 5. "121"：同上
 * 6. "23"：长度2，不是回文（32≠23）
 * 
 * 统计结果：
 * "34543"出现1次
 * "121"出现3次（最多）
 * 输出出现次数最多的"121"及其次数3
 * 
 * 约束：
 * - 输入文本可能有多行
 * - 数字可能非常大，需要字符串处理
 * - 需要处理EOF结束输入
 * - 时间复杂度应优化，避免O(n²)的字符串比较
 * 
 * 算法步骤：
 * 1. 读取输入直到EOF，构建完整字符串
 * 2. 提取所有完整整数（连续数字字符）
 * 3. 过滤：长度≥2，无前导零
 * 4. 检查是否为回文数
 * 5. 使用哈希表/字典统计每个回文数的出现次数
 * 6. 找出最大出现次数
 * 7. 按数字排序输出所有达到最大次数的回文数
 * 
 * 注意：
 * - 数字比较需要按字符串数值比较（长度不同时先比长度）
 * - 输出时按数值从小到大排序
 */
typedef struct{
    ll num;
    int times;

}hw_num;

hw_num hw_nums[1000];
int hw_index = 0;

int cmp(const void* a, const void* b){ 
    ll num1 = *(ll*)a;
    ll num2 = *(ll*)b;
    if(num1 < num2){
        return -1;
    }else if(num1 > num2){
        return 1;
    }else{
        return 0;
    }
}
int is_hw(char* s){
    if(strlen(s) <= 1){
        return 0;
    }
    if(s[0] == '0'){
        return 0;
    }
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        if(s[i] != s[len - 1 - i]){
            return 0;
        }
    }
    return 1;
}
void is_in_hw(ll num){
    for(int i = 0; i < hw_index; i++){
        if(hw_nums[i].num == num){
            hw_nums[i].times++;
            return;
        }
    }
    hw_nums[hw_index].num = num;
    hw_nums[hw_index].times = 1;
    hw_index++;
}
void token_2_ll(char* s){
    ll res = 0;
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        res = res * 10 + (s[i] - '0');
    }
    is_in_hw(res);
}
int main(){
    char s[1000];
    memset(s, '\0', sizeof(s));
    for(int i = 0; i < 1000; i++){
        hw_nums[i].num = 0;
        hw_nums[i].times = 0;
    }
    while(fgets(s, sizeof(s), stdin) != NULL) {
        int index = 0;
        int index_s2 = 0;
        char s2[1000];
        memset(s2, '\0', sizeof(s2));
        while(s[index] != '\n'){
            if(isdigit(s[index])){
                s2[index_s2] = s[index];
                index_s2++;
            }else if(!isdigit(s[index])){
                s2[index_s2] = '*';
                index_s2++;
            }
            index++;
        }
        char* token = strtok(s2, "*");
        while(token != NULL){
            int flag = is_hw(token);
            if(flag == 1){
                token_2_ll(token);
            }
            token = strtok(NULL, "*");
        }

    }
    if(hw_index == 0){
        printf("None\n");
        return 0;
    }
    int max_times = 0;
    for(int i = 0; i < hw_index; i++){
        if(hw_nums[i].times > max_times){
            max_times = hw_nums[i].times;
        }
    }
    int llist_index = 0;
    ll llist[1000];
    for(int i = 0; i < hw_index; i++){
        if(hw_nums[i].times == max_times){
            llist[llist_index] = hw_nums[i].num;
            llist_index++;
        }
    }
    qsort(llist, llist_index, sizeof(ll), cmp);
    for(int i = 0; i < llist_index; i++){
        printf("%lld %d\n", llist[i],max_times);
    }
}
