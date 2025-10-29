#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int input[1000];
    double sum[1000];
    for (int i = 0; i < n; i++){
        scanf("%d", &input[i]);
    }
    for (int i = 0; i<n;i++){
        for (int j = 2; j <= input[i]; j+=2){
            sum[i] += (double) 1.0/j;
        }
    }
    for (int i = 0; i < n; i++){
        printf("%.4f\n", sum[i]);
    }
}