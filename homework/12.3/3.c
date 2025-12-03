#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#define ll long long
/*
 * 题目描述：将7进制数转为2进制数输出
 * 
 * 难度： 简单
 * 
 * 输入：
 * - 第1行：整数n，表示随后有n组数据
 * - 接下来n行：每行一个7进制数m（字符串形式）
 * 
 * 输出：
 * - 对于每组数据：
 *   - 如果是合法的7进制数，输出对应的二进制数
 *   - 如果输入不符合要求，输出"ERROR"
 *   - 每组输出占一行
 * 
 * 要求：
 * - 7进制数必须只包含数字0-6
 * - 如果是合法的7进制数，将其转换为二进制数输出
 * - 如果包含0-6以外的字符，输出"ERROR"
 * 
 * 示例：
 * 输入:
 * 2
 * 3
 * 128
 * 输出:
 * 11
 * ERROR
 * 
 * 解释:
 * "3"是合法的7进制数，转换为二进制是"11"
 * "128"包含数字8，不是合法的7进制数，输出"ERROR"
 */
ll seven_to_ten(int n){
    ll sum = 0,i=0;
    while(n>0){
        sum += (n%10)*(pow(7,i++));
        n /= 10;
    }
    return sum;

}
void ten_to_two(ll n){
    int a[100];
    int max_pos = 0;
    memset(a,0,sizeof(a));
    while(n > 0){
        int temp = log2(n);
        a[temp] = 1;
        n -= pow(2,temp);
        max_pos = max_pos >  temp ? max_pos : temp;
    }
    for(int i = max_pos;i>=0;i--){
        printf("%d",a[i]);
    }
    printf("\n");
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        char s[100];
        memset(s,'\0',sizeof(s));
        scanf("%s",s);
        int err=0;
        for(int i = 0;i<strlen(s);i++){
            if(!isdigit(s[i]) && s[i] != '\0'){
                printf("ERROR\n");
                err = 1;
                continue;
            }
            if(s[i] >= '7' || s[i] < '0'){
                printf("ERROR\n");
                err = 1;
                continue;
            }
        }
        if(err == 1)continue;
        int num = 0;
        int index = 0;
        while(s[index] != '\0'){
            num = num*10 + s[index]-'0';
            index++;
        }
        ten_to_two(seven_to_ten(num));

    }
}