#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"


int is_same(int **a,int **b,int m,int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(a[i][j]!=b[i][j])
                return 0;
        }
    }
    return 1;
}
void move_2_right(int **matrix,int m,int n){
    int **temp = (int **)malloc(m*sizeof(int *));
    for(int i=0;i<m;i++){
        temp[i] = (int *)malloc(n*sizeof(int));
        for(int j=0;j<n;j++){
            temp[i][j] = matrix[i][j];
        }
    }
    for(int i = 0 ; i< m;i++){
        for(int j = 0 ; j< n;j++){
            int new_index = (j+1)%n;
            temp[i][new_index] = matrix[i][j];
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            matrix[i][j] = temp[i][j];
        }
    }
    for(int i=0;i<m;i++){
        free(temp[i]);
    }
    free(temp);

}
void move_2_down(int **matrix,int m,int n){
    int **temp = (int **)malloc(m*sizeof(int *));
    for(int i=0;i<m;i++){
        temp[i] = (int *)malloc(n*sizeof(int));
        for(int j=0;j<n;j++){
            temp[i][j] = matrix[i][j];
        }
    }
    for(int i = 0 ; i< n;i++){
        for(int j = 0 ; j< m;j++){
            int new_index = (j+1)%m;
            temp[new_index][i] = matrix[j][i];
        }

    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            matrix[i][j] = temp[i][j];
        }
    }
    for(int i=0;i<m;i++){
        free(temp[i]);
    }
    free(temp);
}
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    int **a = (int **)malloc(m*sizeof(int *));
    for(int i=0;i<m;i++){
        a[i] = (int *)malloc(n*sizeof(int));
        for(int j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    int **a_cpy = (int **)malloc(m*sizeof(int *));
    for(int i=0;i<m;i++){
        a_cpy[i] = (int *)malloc(n*sizeof(int));
        for(int j=0;j<n;j++){
            a_cpy[i][j] = a[i][j];
        }
    }
    int **b = (int **)malloc(m*sizeof(int *));
    for(int i=0;i<m;i++){
        b[i] = (int *)malloc(n*sizeof(int));
        for(int j=0;j<n;j++){
            scanf("%d",&b[i][j]);
        }
    }
    /*if(is_same(a,b,m,n)){
        printf("0\n");
        return 0;
    }*/
    int step = 0;
    int max_step = m*n;
    int found = 0;
    int s = 1;
    while(1){
        if(s == 1){
            move_2_right(a,m,n);
            step++;
            s = 0;
        }else if(s == 0){
            move_2_down(a,m,n);
            step++;
            s = 1;
        }
        if(step>max_step) break;
        if(is_same(a,b,m,n)){
            found = 1;
            break;
        }
    }
    if(found){
        printf("%d\n",step);
    }else{
        printf("No\n");
    }
}