#include <stdio.h>
/*
 * 题目描述：输出菱形
 *
 * 输入：
 * - 第1行: 整数n, 表示测试数据的组数
 * - 随后n行: 每行一个正整数
 *
 * 输出：
 * - 若输入正整数为奇数，先输出"print"，然后换行输出菱形图案
 * - 若输入正整数不是奇数，输出"error"
 *
 * 要求：
 * - 菱形第一行1个*，第二行3个*，每行递增2个*直到输入的数
 * - 达到最大行后对称递减，直到最后一行1个*
 * - 所有*构成菱形形状，最长行靠左（即左侧无空格）
 *
 * 示例：
 * 输入:
 * 1
 * 5
 * 输出:
 * print
 * *
 * ***
 * *****
 * ***
 * *
 *
 * 约束：
 * - 输入为正整数
 * - 输出格式严格匹配样例
 */
int print_list(int input){
    printf("print\n");
    int space_num = input - 1,star_num = 1; //空格数与*数，第一行*为1
    while (star_num < input){
        for (int j = 0; j < space_num/2; j++){ //对称操作
            printf(" ");
        }
        for (int j = 0; j < star_num; j++){
            printf("*");
        }
        for (int j = 0; j < space_num/2; j++){
            printf(" ");
        }
        space_num -= 2; //每次空格递减2 *递增2
        star_num += 2;
        printf("\n");
    }
    while (star_num > 0){ //打印递减 同理
        for (int j = 0; j < space_num/2; j++){
            printf(" ");
        }
        for (int j = 0; j < star_num; j++){
            printf("*");
        }
        for (int j = 0; j < space_num/2; j++){
            printf(" ");
        }
        space_num += 2;
        star_num -= 2;
        printf("\n");
    }
}
int main(){ 
    int n;
    int list[100];
    scanf ("%d", &n);
    if (n <= 0){
        printf ("error");
        return 0;
    }
    for (int i = 0; i < n; i++){
        scanf ("%d", &list[i]);
    }
    for (int i = 0; i < n; i++){
        if (list[i] <= 0){
            printf ("error");
            continue;
        } else if (list[i] % 2 == 0){
            printf("error\n");
        } else if (list[i] % 2 == 1){
            print_list(list[i]);
        }
    }

}