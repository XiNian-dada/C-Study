#include <stdio.h>
/*
 * 题目描述：分解偶数（哥德巴赫猜想）
 * 
 * 输入：
 * - 每行一个整数n (n ≤ 10000000)
 * 
 * 输出：
 * - 如果n是大于6的偶数：输出所有分解成两个奇质数的组合
 *   按第一个数从小到大排列，每行一个组合，两个数用空格分隔
 * - 如果n不符合要求（n≤6或n为奇数）：输出"ERROR"
 * 
 * 要求：
 * - 任何大于6的偶数都可以分解成两个奇质数的和
 * - 输出所有可能的分解组合
 * - 按第一个质数从小到大排列
 * - 不要重复（如3 7和7 3视为相同，只输出3 7）
 * 
 * 示例：
 * 输入: 10
 * 输出: 
 * 3 7
 * 5 5
 * 
 * 解释:
 * 10可以分解为3+7和5+5
 * 
 * 约束：
 * - n ≤ 10000000
 * - 需要判断输入是否合法（n>6且为偶数）
 */
int is_prime(int n){ 
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++){
        if (n % i == 0) return 0;
    }
    return 1;
}
int main(){
    int input;
    scanf("%d", &input);
    int count = 0;
    for (int i = 1; i <= input/2; i+=2){
        if(is_prime (i) && is_prime(input - i)){
            printf("%d %d\n",i,input - i);
            count++;
        }
        
    }
    if (count == 0) printf("ERROR\n");
}