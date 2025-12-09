#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
/*
 * 题目描述：划行输入识别程序
 * 
 * 难度：困难
 * 
 * 输入格式：
 * - 第1行：整数M，表示折线上关键点的数量
 * - 接下来M行：每行2个浮点数x y，表示关键点的横纵坐标
 * - 接下来1行：整数N，表示词典中单词的个数
 * - 接下来N行：每行一个单词（仅包含26个大写英文字母），长度不超过给定限制
 * 
 * 输出格式：
 * - 若干行：每行一个单词，表示能够被划行输入打出的所有单词
 * - 按照词典输入的顺序输出
 * - 如果没有匹配的单词，输出空（不输出任何内容）
 * 
 * 问题背景：
 * 划行输入是一种触摸屏输入方式，用户用手指在虚拟键盘上滑动轨迹来输入单词。
 * 本题需要根据用户滑动轨迹，从词典中识别出可能想要输入的单词。
 * 
 * 键盘布局（QWERTY键盘在20×6网格中的坐标）：
 * 每个按键占据2×2的正方形区域
 * 左上角为原点(0,0)，向右为x轴正方向，向下为y轴正方向
 * 
 * 轨迹规则：
 * 1. 轨迹由折线表示，包含M个关键点P1,P2,...,PM
 * 2. 折线由M-1条首尾相连的线段组成：P1P2, P2P3, ..., P_{M-1}P_M
 * 3. 识别规则：
 *    a) 单词中的字母顺序必须与划过的键的顺序严格对应
 *    b) 先划过的字母在单词中出现的位置必须在后划过的字母之前
 *    c) 划过的字母可以在单词中出现任意多次，但不能打乱顺序
 *    d) 非关键点上划过的字母，可以出现在单词中，也可以不出现
 *    e) 关键点上划过的字母，必须出现在单词中
 *    f) 特殊情况：
 *       - 线段两个端点在同一个按键中 → 该字母应在单词中连续出现两次
 *       - 连续两条线段的两个关键点在同一个按键中 → 该字母应连续出现三次
 * 
 * 数据保证：
 * 1. 所有线段到任何按键矩形四角的距离都超过10^-6（避免相切情况）
 * 2. 所有关键点都在正方形内部（不在边缘）
 * 3. 轨迹所有线段只会经过键盘上有按键的位置（不会经过空白位置）
 * 
 * 正则表达式表示（辅助理解）：
 * 轨迹可以转换为一个正则表达式模式
 * 例如：AAx*SxWx*EExRxTTx*，其中：
 *   - 大写字母表示该字母必须恰好出现一次
 *   - 小写字母表示该字母可以出现0次到无穷多次
 *   - *代表前面的字符可以出现任意次数（0到无穷）
 * 
 * 示例1：
 * 输入:
 * 3
 * 1.5 3.5
 * 5.0 1.0
 * 9.0 1.0
 * 11
 * [11个单词，包含ASSERT、AET、ASET、AAWET等]
 * 输出:
 * ASSERT
 * AET
 * ASET
 * AAWET
 * AAWETT
 * 
 * 解释：
 * 关键点：(1.5,3.5)→A, (5.0,1.0)→S, (9.0,1.0)→T
 * 轨迹经过字母：ASWERT
 * 必须包含字母：A（关键点1）、S（关键点2）、T（关键点3）
 * 合法单词需按顺序包含A...S...T，且A、S、T必须出现
 * 
 * 示例2：
 * 输入:
 * 2
 * 0.5 0.5
 * 1.5 1.5
 * 5
 * [5个单词，包含QQQ、QQQQ等]
 * 输出:
 * QQQ
 * QQQQ
 * 
 * 约束：
 * - M：关键点数量
 * - N：词典单词数量
 * - 单词长度不超过给定限制
 * - 坐标值为浮点数
 * - 需要处理浮点数精度问题
 * 
 * 提示：
 * 1. 将键盘布局存储为二维字符数组
 * 2. 根据坐标计算对应的按键字母
 * 3. 将轨迹转换为匹配规则（正则表达式形式）
 * 4. 使用贪心匹配策略判断单词是否符合规则
 */

char get_char_from_pos(double x, double y){
    char first_line[10] = {'Q','W','E','R','T','Y','U','I','O','P'};
    char second_line[9] = {'A','S','D','F','G','H','J','K','L'};
    char third_line[7] = {'Z','X','C','V','B','N','M'};
    if(y> 0 && y <= 2){
        int pos = (int) x / 2;
        return first_line[pos];
    }else if (y> 2 && y <= 4){
        int pos = (int) (x-1) / 2;
        return second_line[pos];
    }else if(y> 4 && y <= 6){
        int pos = (int) (x-2) / 2;
        return third_line[pos];
    }
}
int get_pos(char* str, char c){
    int founded = -1;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == c){
            founded = i;
            break;
        }
    }
    return founded;
}
int main(){
    int n;
    scanf("%d", &n);
    char* str = (char*) malloc(n);
    memset(str, '\0', n);
    for(int i = 0; i < n; i++){
        double x, y;
        scanf("%lf %lf", &x, &y);
        str[i] = get_char_from_pos(x, y);
    }
    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        char c[1000];
        memset(c, '\0', 1000);
        scanf("%s", c);
        if(strlen(c) < n){
            continue;
        }
        int position = 0;
        int founded = 0;
        for(int j = 0; j < n; j++){
            int pos = get_pos(c,str[j]);
            if(pos == -1){
                founded = 1;
                break;
            }
            if(pos >= position){
                position = pos;
            }else if(pos < position){
                founded = 1;
            }
        }
        if(founded){
            continue;
        }else{
            printf("%s\n", c);
        }
    }
}


