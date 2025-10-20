#include <stdio.h>

void selection_sort(int arr[],int len){
    
    for(int i=0;i<len;i++){
        int min = i;
        for (int j = i+1;j<len;j++){
            if (arr[j] < arr[min]){
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main(){
    int raw[10] = {6,4,9,8,0,1,3,2,5,7};
    int len = sizeof(raw)/sizeof(raw[0]);

    selection_sort(raw,len);
    for(int i=0;i<10;i++){
        printf("%d ",raw[i]);
    }
}