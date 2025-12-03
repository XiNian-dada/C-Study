#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/*
 * 题目描述：合并有序数组
 * 
 * 难度：简单+
 * 
 * 输入：
 * - 第1行：两个整数m和n (m, n ≥ 0)，分别代表数组a和数组b的长度
 * - 第2行：m个整数，表示有序数组a（升序排列）
 * - 第3行：n个整数，表示有序数组b（升序排列）
 * 
 * 输出：
 * - 一行：合并后的有序数组（升序排列）
 * - 数组元素之间用空格隔开
 * - 最后可以有空格，也可以没有（通常没有多余空格）
 * 
 * 要求：
 * - 将两个有序数组合并为一个有序数组
 * - 合并后的数组仍然保持升序排列
 * - 使用归并排序的合并思路
 * 
 * 示例：
 * 输入:
 * 3 3
 * 1 3 5
 * 2 4 6
 * 输出: 1 2 3 4 5 6
 * 
 * 解释:
 * 数组a = [1, 3, 5]
 * 数组b = [2, 4, 6]
 * 合并后 = [1, 2, 3, 4, 5, 6]
 * 
 * 其他示例：
 * 输入:
 * 2 4
 * 10 20
 * 5 15 25 35
 * 输出: 5 10 15 20 25 35
 * 
 * 输入:
 * 0 3
 * 
 * 1 2 3
 * 输出: 1 2 3
 * 
 * 输入:
 * 3 0
 * 4 5 6
 * 
 * 输出: 4 5 6
 * 
 * 约束：
 * - 0 ≤ m, n ≤ 1000（根据题目环境合理假设）
 * - 数组元素为整数
 * - 输入数组保证是有序的（升序）
 * - 时间复杂度应为O(m+n)
 * - 空间复杂度应合理，可以使用额外数组存储结果
 */
int cmp(const void *a,const void *b){
    return *(int*)a - *(int*)b;
}
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    int* a = (int*)malloc(sizeof(int)*m);
    int* b = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<m;i++){
        scanf("%d",&a[i]);
    }
    getchar();
    for(int i=0;i<n;i++){
        scanf("%d",&b[i]);
    }
    int* c = (int*)malloc(sizeof(int)*(m+n));
    for(int i = 0;i<m;i++){
        c[i] = a[i];
    }
    for(int i = m ,j=0; i<m+n;i++,j++){
        c[i] = b[j];
    }
    qsort(c,m+n,sizeof(int),cmp);
    for(int i = 0;i<m+n;i++){
        printf("%d ",c[i]);
    }
}

