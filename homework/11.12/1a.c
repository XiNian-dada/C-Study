#include "stdio.h"
#include "stdlib.h"
int list[1001];

void init(){
    for(int i=0;i<1001;i++){
        list[i] = 0;
    }
}
int cmp(const void* a,const void* b){
    return (*(int*)a - *(int*)b);
}
int main(){ 
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int j = 0;
        init();
        while(1){
            int a;
            scanf("%d",&a);
            if(a==0){
                break;
            }
            list[j++] = a;
        }
        qsort(list,j,sizeof(int),cmp);
        int flag = 0;
        for(int k = 0;k<j;k++){
            if(list[k]!=k+1 && list[k]!=0){
                printf("%d\n",k+1);
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            printf("%d\n",j+1);
        }
    }
    
}