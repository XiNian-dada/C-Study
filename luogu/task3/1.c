/*
1. P1010 [NOIP 1998 普及组] 幂次方
https://www.luogu.com.cn/problem/P1010
*/
#include <stdio.h>
#include <math.h>
void divide(int x){
    int y = (int ) log2(x);
    if (y == 1){
        printf("%s","2");
    }
    else if (y == 0){
        printf("%s","2(0)");
    }
    else{
        printf("%s", "2(");
        divide(y);
        printf(")");
    }
    if (x - pow(2,y) != 0){
        printf("+");
        divide(x - pow(2,y));
    }
}
int main() {
    int n;
    scanf ("%d", &n);
    divide(n);
    return 0;
}
