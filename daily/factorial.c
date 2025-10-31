#include <stdio.h>

int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(){
    int n;
    printf("请输入一个正整数：");
    scanf("%d", &n);
    printf("n的阶乘是：%d\n", factorial(n));
    return 0;
}