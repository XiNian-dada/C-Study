/*
2: 大小写互换和ASCII码
描述
输入一个字符 ch。
若 ch 为小写字母，输出对应大写字母及其 ASCII 码；
若 ch 为大写字母，输出对应小写字母及其 ASCII 码；
对于其它字符，原样输出该字符及其 ASCII 码。

输入
一个字符。

输出
转换后的字符和十进制ASCII码，中间1个空格。

样例
输入
a

输出
A 65

输入
@

输出
@ 64
*/

#include <stdio.h>

int main()
{
    char input,output;
    scanf("%c",&input);
    if (input >= 'a' && input <= 'z'){
        output = input - 32;
        printf("%c %d",output,input);
    }
    else if (input >= 'A' && input <= 'Z'){
        output = input + 32;
        printf("%c %d",output,input);
    }
    else{
        printf("%c %d",input,input);
    }
}