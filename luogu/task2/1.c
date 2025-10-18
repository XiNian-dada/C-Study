/*
1. P3954 [NOIP 2017 普及组] 成绩
https://www.luogu.com.cn/problem/P3954
*/
#include <stdio.h>

int main()
{
    int a,b,c;
    scanf("%d %d %d", &a, &b, &c);
    int score = a*2 + b*3 +c*5;
    printf("%d", score/10);
    return 0;
}