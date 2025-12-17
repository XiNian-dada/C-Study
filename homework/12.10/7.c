#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

void proc_k1(char** matrix,int m,int n,int k1){
    k1 = k1%n;
    if(k1 == 0){
        return;
    }
    for(int i = 0;i<m;i++){
        char* temp = malloc(n*sizeof(char));
        for(int j = 0;j<n;j++){
            temp[(j+k1)%n] = matrix[i][j];
        }
        for(int j = 0;j<n;j++){
            matrix[i][j] = temp[j];
        }
        free(temp);
    }
    
}
void proc_k2(char** matrix,int m,int n,int k2){
    k2 = k2%m;
    if(k2 == 0){
        return;
    }
    for(int i = 0;i<n;i++){
        char* temp = malloc(m*sizeof(char));

        for(int j = 0;j<m;j++){
            temp[(j+k2)%m] = matrix[j][i];
        }
        for(int j = 0;j<m;j++){
            matrix[j][i] = temp[j];
        }
        free(temp);
    }
    
}

int main(){
    int m,n;
    int k1,k2;
    scanf("%d %d %d %d",&m,&n,&k1,&k2);
    if(m == 1 && n == 1){
        int a;
        scanf("%d",&a);
        printf("%d\n",a);
        return 0;
    }
    char** matrix = (char**)malloc(m*sizeof(char*));
    for(int i=0;i<m;i++){
        matrix[i] = (char*)malloc(n*sizeof(char));
    }
    for(int i=0;i<m;i++){
        scanf("%s",matrix[i]);
    }
    proc_k1(matrix,m,n,k1);
    proc_k2(matrix,m,n,k2);
    for(int i=0;i<m;i++){
        printf("%s\n",matrix[i]);
    }
}

