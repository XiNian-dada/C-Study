#include "stdio.h"
#include "stdlib.h"
#include "math.h"
/*
 * 题目描述：数组的距离
 * 
 * 输入：
 * - 第1行：第一个数组，格式为：元素个数n 后面n个整数
 * - 第2行：第二个数组，格式为：元素个数m 后面m个整数
 * 
 * 输出：
 * - 一个整数：表示两个数组的距离
 * 
 * 要求：
 * - 数组距离定义：从a数组取一个数，从b数组取一个数，计算所有差的绝对值，取其中的最大值
 * - 即 distance = max(|a[i] - b[j]|) 对所有i,j
 * 
 * 计算方法：
 * - 找出a数组的最大值和最小值
 * - 找出b数组的最大值和最小值
 * - 计算：max(|max_a - min_b|, |min_a - max_b|)
 * 
 * 示例：
 * 输入:
 * 3 1 2 3
 * 4 1 2 3 4
 * 输出: 3
 * 解释: 
 * a数组：1,2,3 → min=1, max=3
 * b数组：1,2,3,4 → min=1, max=4
 * 距离 = max(|3-1|, |1-4|) = max(2,3) = 3
 * 
 * 约束：
 * - 数组元素个数n ≤ 10
 * - 数组元素为整数
 */
int cmp(const void *a,const void *b){
    return (- *(int*)a + *(int*)b);
}
int cmp_2(const void *a,const void *b){
    return (*(int*)a - *(int*)b);
}
int main(){
    int n,m;
    int nl[1000],ml[1000];
    for(int i = 0;i < 1000;i++){
        nl[i] = 0;
        ml[i] = 0;
    }
    scanf("%d",&n);
    for(int i = 0;i < n;i++){
        scanf("%d",&nl[i]);
    }
    getchar();
    scanf("%d",&m);
    for(int i = 0;i < m;i++){
        scanf("%d",&ml[i]);
    }
    qsort(nl,n,sizeof(nl[0]),cmp_2);
    qsort(ml,m,sizeof(ml[0]),cmp);
    int biggest = abs(nl[0] - ml[0]);
    qsort(nl,n,sizeof(nl[0]),cmp);
    qsort(ml,m,sizeof(ml[0]),cmp_2);
    biggest = abs(nl[0] - ml[0]) > biggest ? abs(nl[0] - ml[0]) : biggest;
    printf("%d",biggest);

}