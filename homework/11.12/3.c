#include "stdio.h"
/*
 * 题目描述：分解质因数
 * 
 * 输入：
 * - 第1行: 整数n, 表示测试数据的组数
 * - 随后n行: 每行一个整数num
 * 
 * 输出：
 * - n行: 每行一个字符串，表示num的质因数分解形式
 * 
 * 要求：
 * - 将num表示为质因数相乘的形式
 * - 质因数按照从小到大的顺序排列
 * - 用"*"连接各个质因数
 * - 如果num本身是质数或1，直接输出该数
 * 
 * 示例：
 * 输入:
 * 3
 * 1
 * 11
 * 12
 * 输出:
 * 1
 * 11
 * 2*2*3
 * 
 * 解释:
 * 1的质因数分解就是1
 * 11是质数，直接输出11
 * 12 = 2 × 2 × 3
 * 
 * 约束：
 * - 输入为整数
 * - 需要处理1和质数的特殊情况
 */
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}
void divide(int n,int is_first){
    for(int i = 2; i <= n; i++){
        if(n == 1){
            break;
        }
        if(is_prime(i) && n % i == 0){
            if(is_first){
                printf("%d", i);
                divide(n / i, 0);
                break;
            }else{
                printf("*%d", i);
                divide(n / i, 0);
                break;
            }
        }
        
    }
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int a;
        scanf("%d", &a);
        if(a == 1){
            printf("1\n");
            continue;
        }
        if(is_prime(a)){
            printf("%d\n", a);
            continue;
        }else{
            divide(a, 1);
            printf("\n");
        }
    }
}