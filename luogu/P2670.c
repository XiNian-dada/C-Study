#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // 使用固定大小数组避免兼容性问题
    char list[105][105];
    
    // 读取输入数据
    for(int i = 0; i < n; i++) {
        getchar(); // 跳过换行符
        for(int j = 0; j < m; j++) {
            scanf("%c", &list[i][j]);
        }
    }
    
    // 处理每个格子
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(list[i][j] == '?') {
                int count = 0;
                // 检查8个方向的相邻格子
                for(int di = -1; di <= 1; di++) {
                    for(int dj = -1; dj <= 1; dj++) {
                        if(di == 0 && dj == 0) continue; // 跳过自己
                        int ni = i + di;
                        int nj = j + dj;
                        // 检查边界
                        if(ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            if(list[ni][nj] == '*') {
                                count++;
                            }
                        }
                    }
                }
                printf("%d", count);
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
    
    return 0;
}