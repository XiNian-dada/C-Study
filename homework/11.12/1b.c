#include "stdio.h"

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int max=0,min=0,sum_expect=0,sum_actual=0;
        while(1){
            int temp;
            scanf("%d",&temp);
            if(temp==0){
                break;
            }
            sum_actual+=temp;
            max = temp>max?temp:max;
            min = temp<min?temp:min;
        }
        sum_expect = (max + min) * (max - min + 1) / 2;
        printf("%d\n",sum_expect-sum_actual);
    }
}