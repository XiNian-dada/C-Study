#include <stdio.h>

int devide_number(int a){
    int temp[100];
    int i =0;
    if (a < 10){
        return a;
    }
    if (a >= 10){
        while (a > 0){
            temp[i] = a%10;
            a = a/10;
            i++;
        }
        int sum = 0;
        for (int j = 0; j < i; j++){
            sum += temp[j];
        }
        return devide_number(sum);
    }
    
}
int main(){
    int input;
    scanf("%d", &input);
    printf("%d", devide_number(input));
}