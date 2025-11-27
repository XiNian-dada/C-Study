#include "stdio.h"
#include "stdlib.h"
/*
 * 题目描述：报数游戏（约瑟夫环变种）
 * 
 * 难度：中等
 * 
 * 输入：
 * - 第1行：整数n，表示测试用例组数
 * - 随后n行：每行一个正整数m (m > 3)，表示每组测试的人数
 * 
 * 输出：
 * - n行：每行一个整数，表示最后剩下的人最初的编号
 * 
 * 要求：
 * - m个人围成一圈，从第1个人开始报数：1,2,3,1,2,3...
 * - 凡报到3的人退出圈子
 * - 求最后剩下的人最初的位置编号
 * 
 * 游戏规则：
 * - 报数循环：1→2→3→1→2→3...
 * - 报到3的人立即退出
 * - 从退出者的下一个人继续报数
 * - 直到只剩一人为止
 * 
 * 示例：
 * 输入:
 * 2
 * 4
 * 10
 * 输出:
 * 1
 * 4
 * 
 * 解释:
 * 当m=4时：初始位置1,2,3,4
 *   第1轮：报数1(1),2(2),3(3出局) → 剩余1,2,4
 *   第2轮：报数1(4),2(1),3(2出局) → 剩余1,4  
 *   第3轮：报数1(1),2(4),3(1出局) → 剩余4
 *   最后剩下的是最初位置4的人
 * 
 * 提示：
 * 当只剩2人A,B时：A报1→B报2→A报3(A出局)→剩下B
 * 
 * 约束：
 * - m > 3
 * - 需要模拟约瑟夫环过程
 */
typedef struct{
    int index;
    int is_alive;
}player;
void process(player* players,int start_num,int player_num){
    int num = start_num;
    int alive_num = player_num;
    if(alive_num == 1){
        printf("%d\n", players[0].index);
    }
    for(int i = 0; i < player_num; i++){
        if(num == 3){
            players[i].is_alive = 0;
            num = 1;
            alive_num--;
        }else{
            num++;
            players[i].is_alive = 1;
        }
    }
    player* alive_player = (player*)malloc(alive_num * sizeof(player));
    int j = 0;
    for(int i = 0; i < player_num; i++){
        if(players[i].is_alive == 1){
            alive_player[j] = players[i];
            j++;
        }else{
            continue;
        }
    }
    if(alive_num == 1){
        printf("%d\n", alive_player[0].index);
    }else{
        process(alive_player, num, alive_num);
    }
    
}
int main(){
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        
        int num;
        scanf("%d", &num);
        player *players = (player*)malloc(num * sizeof(player));
        for(int j = 0; j < num; j++){
            players[j].index = j + 1;
            players[j].is_alive = 1;
        }
        process(players, 1, num);
        free(players);
    }
   
}
