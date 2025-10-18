/*
3. P1307 [NOIP 2011 普及组] 数字反转
https://www.luogu.com.cn/problem/P1307
*/
#include <stdio.h>

int main() {
    int n, reversed = 0;
    
    scanf("%d", &n);
    
    if (n < 0) {
        printf("-");
        n = -n;
    }
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    
    printf("%d", reversed);
    return 0;
}