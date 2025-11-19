#include "stdio.h"
/*
 * 题目描述：将数组中的0移到末尾
 * 
 * 输入：
 * - 第1行：整数n，表示测试数据的组数
 * - 每组数据包含：
 *     - 第1行：整数m，表示数组元素个数
 *     - 第2行：m个整数，表示数组元素
 * 
 * 输出：
 * - 对每组数据：输出处理后的数组，0移到末尾，非0元素保持原顺序
 * - 元素间用空格分隔，每组输出占一行
 * 
 * 要求：
 * - 将数组中所有的0移动到数组末尾
 * - 非0元素保持原来的相对顺序
 * - 输出时元素间用空格分隔
 * 
 * 示例：
 * 输入:
 * 1
 * 10
 * 1 2 0 6 4 0 8 0 9 18
 * 输出:
 * 1 2 6 4 8 9 18 0 0 0
 * 
 * 解释:
 * 原数组: [1,2,0,6,4,0,8,0,9,18]
 * 移动后: [1,2,6,4,8,9,18,0,0,0]
 * 非0元素顺序保持不变，所有0移到末尾
 * 
 * 约束：
 * - 数组元素为整数
 * - 需要保持非0元素的原始顺序
 */
int main(){
    int list[1001];
    int answer[1001];
    int n;
    int m;
    

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d",&m);
        int zero_count = 0;
        for(int j = 0; j < 1001; j++){
            answer[j] = 0;
        }
        for(int j = 0; j < m; j++){
            scanf("%d", &list[j]);
        }
        int index =0;
        for(int j = 0; j < m; j++){

            if(list[j] == 0){
                zero_count++;
                continue;
            }else{
                answer[index++] = list[j];
            }
        }
        for(int j = 0; j < index; j++){
            printf("%d ", answer[j]);


        }
        for(int j = 0; j < zero_count; j++){
            printf("0 ");
        }
        printf("\n");

    }


}