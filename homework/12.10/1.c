#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

void bias_pr(char *a,int n,int k){
    char *b = (char*)malloc(sizeof(char)*n);
    
    for(int i = 0; i < n; i++){
        int new_index = (i+k)%n;
        b[new_index] = a[i];
    }
    for(int i = 0; i < n; i++){
        printf("%c",b[i]);
    }
    printf("\n");
}
int main(){
    int m,n;
    int k;
    scanf("%d %d %d",&m,&n,&k);
    for(int i = 0; i < m; i++){
        char* s = (char*)malloc(sizeof(char)*n);
        scanf("%s",s);
        bias_pr(s,n,k);
    }
}

