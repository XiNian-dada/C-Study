#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(){
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);

    int** matrix = (int**)malloc(m * sizeof(int*));
    for(int i = 0; i < m; i++){
        matrix[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    if (2 * k > m + 1 || 2 * k > n + 1) {
        printf("0\n");
        for(int i = 0; i < m; i++) free(matrix[i]);
        free(matrix);
        return 0;
    }
    
    int sum = 0; 
    
    int top = k - 1;
    int bottom = m - k;
    int left = k - 1;
    int right = n - k;
    if(top == bottom && left == right){
        sum += matrix[top][left];
        printf("%d\n", sum);
        return 0;
    }
    // left top -> right top
    for(int i = left ; i <= right; i++){
        sum += matrix[top][i];
        matrix[top][i] = 0;
    }
    // right top -> right bottom
    for(int i = top + 1; i <= bottom; i++){
        sum += matrix[i][right];
        matrix[i][right] = 0;
    }
    // right bottom -> left bottom
    for(int i = right - 1; i >= left; i--){
        sum += matrix[bottom][i];
        matrix[bottom][i] = 0;
    }
    // left bottom -> left top
    for(int i = bottom - 1; i >= top + 1; i--){
        sum += matrix[i][left];
        matrix[i][left] = 0;
    }
    printf("%d\n", sum);
    
    
}