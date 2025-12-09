#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
int map[10][10];
int fragment[4][4];
int size = 0;
int** opt_fragment;
/*
 * 题目描述：礼物拼图放置问题
 * 
 * 难度：中等+
 * 
 * 输入：
 * - 第1-10行：每行10个整数（0或1），表示10×10的拼图棋盘
 *   - 1：该格子已有拼图
 *   - 0：该格子为空，可以放置拼图碎片
 * - 第11-14行：每行4个整数（0或1），表示4×4的拼图碎片形状
 *   - 1：表示拼图碎片占据的位置
 *   - 0：表示空白位置
 *   - 所有为1的格子构成一个完整的连通块（即碎片形状是连通的）
 * 
 * 输出：
 * - 一个整数：表示拼图碎片可以在棋盘中放置的位置数量
 * 
 * 放置规则：
 * 1. 拼图碎片不能旋转（方向固定）
 * 2. 拼图碎片必须完全放置在棋盘内（4×4碎片放置在10×10棋盘）
 * 3. 拼图碎片的每个'1'位置必须对应棋盘的'0'位置（即空位）
 * 4. 拼图碎片不能覆盖棋盘上已有的拼图（'1'位置）
 * 5. 拼图碎片的所有'1'格子必须全部放置在棋盘空位上
 * 
 * 算法：
 * 1. 拼图碎片大小为4×4，棋盘大小为10×10
 * 2. 碎片可以放置在棋盘上的起始位置范围：(0,0)到(6,6)（包含）
 *    - 因为碎片宽度4，棋盘宽度10，所以水平方向有10-4+1=7个起始位置
 *    - 垂直方向同理
 * 3. 对于每个可能的起始位置(i,j)（i=0..6, j=0..6）：
 *    - 检查碎片所有'1'位置对应的棋盘位置是否都为'0'
 *    - 如果所有对应位置都为空，则该位置可以放置
 * 4. 统计所有可以放置的位置数量
 * 
 * 示例1：
 * 输入:
 * 前10行：棋盘状态
 * 后4行：
 * 0 0 0 0
 * 0 1 1 1
 * 0 0 1 0
 * 0 0 0 0
 * 输出:
 * 1
 * 
 * 解释：
 * 碎片形状：
 * [0 0 0 0]
 * [0 1 1 1]
 * [0 0 1 0]
 * [0 0 0 0]
 * 碎片占据位置：(1,1),(1,2),(1,3),(2,2)（行号从0开始，列号从0开始）
 * 
 * 棋盘第7行（索引6）和第8行（索引7）有足够的空位：
 * 只有起始位置(6,2)可以放置：
 * - 碎片(1,1)对应棋盘(7,3)：空位
 * - 碎片(1,2)对应棋盘(7,4)：空位
 * - 碎片(1,3)对应棋盘(7,5)：空位
 * - 碎片(2,2)对应棋盘(8,4)：空位
 * 其他位置都会覆盖已有拼图或超出边界
 * 
 * 示例2：
 * 输入:
 * 棋盘有更多空位
 * 相同碎片
 * 输出:
 * 3
 * 
 * 解释：
 * 棋盘第7行（索引6）有连续多个空位，碎片可以在多个起始位置放置：
 * 起始位置(6,0)、(6,1)、(6,2)都可以放置
 * 
 * 约束：
 * - 输入保证碎片所有'1'格子构成一个连通块
 * - 不需要验证碎片的连通性（题目已保证）
 * - 棋盘边界明确：10×10
 * - 碎片大小明确：4×4
 * - 碎片不可旋转
 * 
 * 实现提示：
 * 1. 使用二维数组存储棋盘和碎片
 * 2. 双重循环遍历所有可能的起始位置
 * 3. 对于每个起始位置，检查碎片所有'1'位置
 * 4. 注意数组索引从0开始
 * 5. 时间复杂度：O(7×7×16)=O(784)，可以接受
 */
int main(){
    memset(map,0,sizeof(map));
    for(int i=0;i<10;i++){
    
        for(int j=0;j<10;j++){
            scanf("%d",&map[i][j]);
        }
        getchar();
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            scanf("%d",&fragment[i][j]);
            if(fragment[i][j]==1){
                size++;
            }
        }
        getchar();
    }

    int min_row = 4, max_row = -1;
    int min_col = 4, max_col = -1;
    int opt_rows = 0, opt_cols = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(fragment[i][j] == 1) {
                if(i < min_row) min_row = i;
                if(i > max_row) max_row = i;
                if(j < min_col) min_col = j;
                if(j > max_col) max_col = j;
            }
        }
    }
    if(max_row >= 0) {
        opt_rows = max_row - min_row + 1;
        opt_cols = max_col - min_col + 1;
        
        opt_fragment = (int**)malloc(sizeof(int*) * opt_rows);
        for(int i = 0; i < opt_rows; i++) {
            opt_fragment[i] = (int*)malloc(sizeof(int) * opt_cols);
        }
        
        for(int i = 0; i < opt_rows; i++) {
            for(int j = 0; j < opt_cols; j++) {
                opt_fragment[i][j] = fragment[min_row + i][min_col + j];
            }
        }
        
    }
    int count = 0;
    for(int i = 0; i <= 10 - opt_rows ; i++){
        for(int j = 0; j <= 10 - opt_cols ; j++){ 
            int size_cp = size;
            for(int k = 0; k < opt_rows ; k++){ 
                for(int l = 0; l < opt_cols ; l++){
                    if(opt_fragment[k][l] ==1 && map[i+k][j+l] == 0){
                        size_cp--;
                    }
                }
            }
            if(size_cp == 0){
                count++;
            }
        }
    }
    printf("%d",count);
    

}

