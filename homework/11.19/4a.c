#include "stdio.h"
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
int main(){
    int n,m,nl[1000],ml[1000],max_1=0,min_1=1000,max_2=0,min_2=1000;
    scanf("%d",&n);
    for(int i=0;i<n;scanf("%d",&nl[i++]));
    scanf("%d",&m);
    for(int i=0;i<m;scanf("%d",&ml[i++]));
    for(int i=0;i<m;max_1 = ml[i]>max_1?ml[i]:max_1,min_1 = ml[i]<min_1?ml[i]:min_1,i++);
    for(int i=0;i<n;max_2 = nl[i]>max_2?nl[i]:max_2,min_2 = nl[i]<min_2?nl[i]:min_2,i++);
    printf("%d\n",(max_1-min_2 > max_2-min_1?max_1-min_2:max_2-min_1) < 0 ? -((max_1-min_2 > max_2-min_1?max_1-min_2:max_2-min_1)):(max_1-min_2 > max_2-min_1?max_1-min_2:max_2-min_1));
}