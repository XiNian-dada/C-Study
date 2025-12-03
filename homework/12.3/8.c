#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
/*
 * 题目描述：新报数游戏2
 * 
 * 难度：中等+
 * 
 * 输入：
 * - 第1行：整数n，表示测试用例的数量
 * - 接下来n行：每行一个正整数m，表示每组测试的人数
 * 
 * 输出：
 * - 对于每组测试，输出一行：最后剩下的人最开始的位置编号（从1开始计数）
 * 
 * 规则：
 * m个人围成一圈，从第1个人开始顺序报数：1, 2, 3, 4, ...
 * 报数规则：
 * 1. 报数数字从1开始，连续递增
 * 2. 只有当前活着的人才参与报数（被淘汰的人跳过）
 * 3. 当报到的数字满足以下条件之一时，该人立即淘汰出局：
 *    a. 数字是7的倍数（如7, 14, 21, ...）
 *    b. 数字的十进制表示中包含数字7（如7, 17, 27, ..., 70, 71, 72, ...）
 * 4. 淘汰后游戏继续，报数数字继续递增，下一个活着的人报下一个数字
 * 5. 重复以上过程，直到只剩下一个人
 * 
 * 关键点：
 * - 报数数字连续递增，不会因为有人淘汰而重置
 * - 被淘汰的人不再参与后续报数（跳过该位置）
 * - 数字7同时满足两个淘汰条件（是7的倍数且包含数字7）
 * - 需要模拟整个游戏过程
 * 
 * 示例：
 * 输入:
 * 2
 * 10
 * 20
 * 
 * 输出:
 * 10
 * 5
 * 
 * 约束：
 * - 7 < m < 1000
 * - 需要处理多组测试数据
 * - 输出最后剩下的人的初始编号（1-based）
 */
typedef struct{
    int index;
    int is_alive; //1 live 0 dead
}player;
int include_7(int n);
void kill(player *p,int total_num){
    int alive_num=total_num;
    int num=1;
    int index=0;
    while(alive_num>1){
        if(p[index].is_alive==1){
            if(include_7(num)){
                p[index].is_alive=0;
                alive_num--;
            }
            num++;
            index++;
            if(index >= total_num) index=0;
        }else{
            index++;
            if(index >= total_num) index=0;
        }
    }
    for(int i=0;i<total_num;i++){
        if(p[i].is_alive==1){
            printf("%d\n",p[i].index);
            return;
        }
    }
}
int include_7(int n){
    if(n % 7 == 0) return 1;
    int temp[1000];
    int i = 0;
    while(n>0){
        temp[i]=n%10;
        n=n/10;
        i++;
    }
    for(int j = i-1;j>=0;j--){
        if(temp[j]==7){
            return 1;
        }
    }
    return 0;
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int m;
        scanf("%d",&m);
        player *p=(player*)malloc(sizeof(player)*m);
        for(int j=0;j<m;j++){
            p[j].index=j+1;
            p[j].is_alive=1;
        }
        kill(p,m);
    }

}

