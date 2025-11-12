#include "stdio.h"
/*
 * 题目描述：新斐波那契数列
 * 
 * 输入：
 * - 第1行: 整数n, 表示测试数据的组数
 * - 随后n行: 每行一个整数m (m ≤ 30)，表示新斐波那契数列的下标
 * 
 * 输出：
 * - n行: 每行一个long long整数，表示新斐波那契数列第m项的值
 * 
 * 要求：
 * - 计算新斐波那契数列：F(m) = 2*F(m-1) + 3*F(m-2) + 5*F(m-3)
 * - 初始条件：F(1) = F(2) = F(3) = 1
 * - 使用long long类型存储结果
 * 
 * 递归定义：
 * - 基准情况：F(1) = 1, F(2) = 1, F(3) = 1
 * - 递归情况：F(m) = 2*F(m-1) + 3*F(m-2) + 5*F(m-3) (m > 3)
 * 
 * 示例：
 * 输入:
 * 3
 * 9
 * 16
 * 28
 * 输出:
 * 3493
 * 16357465
 * 32002027134220
 * 
 * 约束：
 * - m ≤ 30
 * - 结果可能很大，需使用long long类型
 * - 输出格式：%lld
 */
#define ll long long
ll new_fib(ll n){
    if(n==0||n==1||n==2||n==3){
        return 1;
    }else{return(2*new_fib(n-1)+3*new_fib(n-2)+5*new_fib(n-3));}
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        printf("%lld\n",new_fib(a));
    }
}