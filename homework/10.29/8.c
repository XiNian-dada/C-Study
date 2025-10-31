#include <stdio.h>
#include <ctype.h>
/*
 * 题目描述：去除空白
 * 
 * 输入：
 * - 一行或多行文本，总长度 ≤ 1000，以EOF结束
 * - 字符串包含可见ASCII字符和空白字符（空格、制表符、换行、回车）
 * 
 * 输出：
 * - 一行，处理后的字符串
 * 
 * 要求：
 * - 删除字符串开始的所有空白字符
 * - 将所有连续的空白字符压缩为单个空格
 * - 保留字符串末尾的空格（如果有的话）
 * - 输出为单行文本
 * 
 * 处理规则：
 * 1. 去除开头的所有空白
 * 2. 将连续的空白字符（空格、制表符、换行、回车）替换为单个空格
 * 3. 保留非空白字符之间的单个空格分隔
 * 
 * 示例：
 * 输入: "Hello    world!\n   This   is   a   test."
 * 输出: "Hello world! This is a test."
 * 
 * 输入: "   Leading and trailing spaces "
 * 输出: "Leading and trailing spaces"
 * 
 * 约束：
 * - 总输入长度 ≤ 1000
 * - 以EOF结束输入
 * - 包含可见ASCII字符和空白字符
 */
int main(){
    int ch;
    //记录是否为第一个单词，第一个单词之前空格要全部删掉
    int first_word = 1;
    //记录是否需要空格，比如一个单词的末尾，或者一个符号
    int space_needed = 0;
    //当没有结束输入时执行
    while((ch = getchar()) != EOF){

        //如果是空字符，并且是首单词之前的，continue跳过本次循环
        if(isspace(ch) && first_word){
            continue;
        }
        //如果是字母，输出它，然后把首单词修改为false即0
        //同时，修改需要输出空格，这样在遇到单词间的空隙时就可以依据它来保留空格
        if(isalpha(ch)){
            putchar(ch);
            first_word = 0;
            space_needed = 1;
        //如果是符号的话，同上，但理论上开头不可能是符号所以就不修改first_word了，也没啥用了后面，一次性变量
        }else if (ispunct(ch)){
            putchar(ch);
            space_needed = 1;
        }
        //如果是空符号，并且需要空格
        //那就输出空格，并把space_needed修改为0保证只有一个空格
        if (isspace(ch) && space_needed){
            putchar(' ');
            space_needed = 0;
        } 
    }
    return 0;

}
