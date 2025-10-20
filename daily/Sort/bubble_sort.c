#include <stdio.h>  


int main(void){
    int raw[10] = {1,6,9,3,4,8,2,5,7,0};
    for (int i=0;i<9;i++){
        for (int j =0;j<9;j++){
            if (raw[j + 1] < raw[j]){
                int temp = raw[j+1];     
                raw[j+1] = raw[j];
                raw[j] = temp;
            }
        }
    }
    for (int i = 0;i<10;i ++){
        printf("%d",raw[i]);
    }
}