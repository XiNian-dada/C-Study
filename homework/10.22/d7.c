/*7: 判断闰年
描述
输入一个整数表示年份，判断此年份是不是闰年

输入
第1行是一个整数n，表示随后有n组数据。

每组数据占一行，包含一个整数，表示年份。

输出
对于每一组数据，若是合理年份（大于0）且是闰年，则输出yes，否则输出no。

样例
输入
2
2016
2017

输出
yes
no
闰年
如果一个年份能被400整除，它是闰年；
如果一个年份能被100整除但不能被400整除，它不是闰年；
如果一个年份能被4整除但不能被100整除，它是闰年；
其余年份都不是闰年。*/
#include <stdio.h>
int main(){
    int num;
    int year[100000];
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d\n", &year[i]);
    }
    for (int i = 0; i < num; i++)
    {
        if (year[i] <= 0)
        {
            printf("no\n");
            continue;
        }
        if (year[i] % 400 == 0 || (year[i] % 100 != 0 && year[i] % 4 == 0))
        {
            printf("yes\n");
        } else
        {
            printf("no\n");
        }
    }

}