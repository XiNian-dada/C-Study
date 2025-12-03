#include "stdio.h"
#include "stdlib.h"
#define ll long long
/*
 * 题目描述：矩阵的幂
 * 
 * 难度：中等
 * 
 * 输入：
 * - 第1行：两个整数n和k，用空格分隔
 *   - n：矩阵的阶数（n×n矩阵）
 *   - k：矩阵A的幂次（计算A^k）
 * - 接下来n行：每行n个整数，用空格分隔，表示矩阵A的元素
 * 
 * 输出：
 * - 输出n行，每行n个整数（用空格分隔），表示矩阵A^k的结果
 * 
 * 要求：
 * - 计算矩阵A的k次方：A^k = A × A × ... × A（k个A相乘）
 * - 使用标准矩阵乘法规则
 * 
 * 矩阵乘法公式详细解释：
 * 设矩阵A和B都是n×n矩阵，它们的乘积C = A × B定义为：
 * C[i][j] = Σ(A[i][p] × B[p][j])，其中求和p从0到n-1
 * 
 * 具体来说：
 * 1. C的第i行第j列元素 = A的第i行每个元素与B的第j列对应元素乘积之和
 * 2. 计算过程：
 *    C[i][j] = 0
 *    for p = 0 to n-1:
 *        C[i][j] += A[i][p] * B[p][j]
 * 
 * 矩阵的幂：
 * A^1 = A
 * A^2 = A × A
 * A^3 = A × A × A = (A × A) × A 或 A × (A × A)（矩阵乘法满足结合律）
 * 依此类推
 * 
 * 两个不同矩阵相乘的详细示例：
 * 假设有两个2×2矩阵：
 * A = [a11 a12]    B = [b11 b12]
 *     [a21 a22]        [b21 b22]
 * 
 * 那么C = A × B的计算为：
 * C[1][1] = a11×b11 + a12×b21  （A第1行与B第1列的点积）
 * C[1][2] = a11×b12 + a12×b22  （A第1行与B第2列的点积）
 * C[2][1] = a21×b11 + a22×b21  （A第2行与B第1列的点积）
 * C[2][2] = a21×b12 + a22×b22  （A第2行与B第2列的点积）
 * 
 * 所以结果矩阵C为：
 * C = [a11×b11 + a12×b21  a11×b12 + a12×b22]
 *     [a21×b11 + a22×b21  a21×b12 + a22×b22]
 * 
 * 注意：矩阵乘法不满足交换律，即A×B ≠ B×A（一般情况下）
 * 
 * 矩阵幂的特殊情况：
 * 1. 当计算A^k时，实际上进行了k-1次矩阵乘法
 * 2. 可以使用快速幂算法优化，但本题规模较小可以直接计算
 * 
 * 示例：
 * 输入:
 * 3 2
 * 2 1 5
 * 2 5 7
 * 7 3 3
 * 
 * 输出:
 * 41 22 32
 * 63 48 66
 * 41 31 65
 * 
 * 解释:
 * 矩阵A为：
 * [2 1 5]
 * [2 5 7]
 * [7 3 3]
 * 
 * 计算A^2 = A × A：
 * 
 * 第一行第一列：2×2 + 1×2 + 5×7 = 4 + 2 + 35 = 41
 * 第一行第二列：2×1 + 1×5 + 5×3 = 2 + 5 + 15 = 22
 * 第一行第三列：2×5 + 1×7 + 5×3 = 10 + 7 + 15 = 32
 * 
 * 第二行第一列：2×2 + 5×2 + 7×7 = 4 + 10 + 49 = 63
 * 第二行第二列：2×1 + 5×5 + 7×3 = 2 + 25 + 21 = 48
 * 第二行第三列：2×5 + 5×7 + 7×3 = 10 + 35 + 21 = 66
 * 
 * 第三行第一列：7×2 + 3×2 + 3×7 = 14 + 6 + 21 = 41
 * 第三行第二列：7×1 + 3×5 + 3×3 = 7 + 15 + 9 = 31
 * 第三行第三列：7×5 + 3×7 + 3×3 = 35 + 21 + 9 = 65
 * 
 * 边界情况：
 * 1. 当k=1时，直接输出原矩阵
 * 2. 当k=0时，输出单位矩阵（但题目中k≥1）
 * 
 * 约束：
 * - 1 ≤ n, k ≤ 7
 * - 1 ≤ A[i][j] ≤ 7
 * - 中间结果和最终结果可能超过int范围，但根据约束可计算
 * - 矩阵元素用空格分隔，每行输出后换行
 */
void matrix_multiply(ll** matrix, ll** matrix_cpy, int n, int k){
    ll temp[7][7];

    for(int step = 1; step < k; step++){ 

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                temp[i][j] = 0;
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int l=0;l<n;l++){
                    temp[i][j] += matrix[i][l] * matrix_cpy[l][j];
                }
            }
        }
        for(int i=0;i<n;i++){

            for(int j=0;j<n;j++){
                matrix[i][j] = temp[i][j];
    
                }
            }
        }
}
int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    ll** matrix=(ll**)malloc(n*sizeof(ll*));
    ll** matrix_cpy=(ll**)malloc(n*sizeof(ll*));
    for(int i=0;i<n;i++){
        matrix[i]=(ll*)malloc(n*sizeof(ll));
        matrix_cpy[i]=(ll*)malloc(n*sizeof(ll));
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%lld",&matrix[i][j]);
            matrix_cpy[i][j]=matrix[i][j];
        }
    }
    if(k == 0){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i == j) printf("1 ");
                else printf("0 ");
            }
            printf("\n");
        }
        return 0;
    }
    matrix_multiply(matrix,matrix_cpy,n,k);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%lld", matrix[i][j]);
            if(j != n-1) printf(" ");
        }
        printf("\n");
    }
    
}
