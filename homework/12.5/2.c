#include "stdio.h"
#include "stdlib.h"
#define ll long long
int main(){
    int n;
    scanf("%d",&n);
    int *arr = (int*)malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        scanf("%d",&arr[i]);
    }
    ll count = 0;
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j< n-1-i ; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                count++;
            }
        }
    }
    printf("%lld",count);
}