/*
7. P1205 [USACO1.2] 方块转换 Transformations
https://www.luogu.com.cn/problem/P1205
*/
#include <stdio.h>
#include <string.h>

int n;
// AI写的也是错的，我更不会了，开始想的是储存到二维列表里面然后进行坐标变换，然后发现自己的数学水平才是瓶颈，寄了
// 90度顺时针旋转
void rotate90(char src[][11], char dst[][11]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i][j] = src[n-1-j][i];
        }
    }
}

// 水平翻转（左右镜像）
void reflect(char src[][11], char dst[][11]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i][j] = src[i][n-1-j];
        }
    }
}

// 比较两个矩阵是否相同
int isEqual(char a[][11], char b[][11]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(a[i], b[i]) != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    
    char original[11][11];  // 原始矩阵
    char target[11][11];    // 目标矩阵
    char temp[11][11];      // 临时矩阵
    
    // 读取原始矩阵
    for (int i = 0; i < n; i++) {
        scanf("%s", original[i]);
    }
    
    // 读取目标矩阵
    for (int i = 0; i < n; i++) {
        scanf("%s", target[i]);
    }
    
    // 检查1: 90度旋转
    rotate90(original, temp);
    if (isEqual(temp, target)) {
        printf("1\n");
        return 0;
    }
    
    // 检查2: 180度旋转（基于原始矩阵重新计算）
    char temp180[11][11];
    rotate90(temp, temp180);  // 基于90度结果再旋转90度得到180度
    if (isEqual(temp180, target)) {
        printf("2\n");
        return 0;
    }
    
    // 检查3: 270度旋转（基于原始矩阵重新计算）
    char temp270[11][11];
    rotate90(temp180, temp270);  // 基于180度结果再旋转90度得到270度
    if (isEqual(temp270, target)) {
        printf("3\n");
        return 0;
    }
    
    // 检查4: 水平翻转
    reflect(original, temp);
    if (isEqual(temp, target)) {
        printf("4\n");
        return 0;
    }
    
    // 检查5: 组合变换（先反射，再旋转90/180/270度）
    char reflected[11][11];
    reflect(original, reflected);
    
    // 反射后旋转90度
    rotate90(reflected, temp);
    if (isEqual(temp, target)) {
        printf("5\n");
        return 0;
    }
    
    // 反射后旋转180度（基于反射矩阵重新计算）
    char temp5_180[11][11];
    rotate90(temp, temp5_180);
    if (isEqual(temp5_180, target)) {
        printf("5\n");
        return 0;
    }
    
    // 反射后旋转270度（基于反射矩阵重新计算）
    char temp5_270[11][11];
    rotate90(temp5_180, temp5_270);
    if (isEqual(temp5_270, target)) {
        printf("5\n");
        return 0;
    }
    
    // 检查6: 不改变
    if (isEqual(original, target)) {
        printf("6\n");
        return 0;
    }
    
    // 如果都不是，则为无效转换
    printf("7\n");
    return 0;
}