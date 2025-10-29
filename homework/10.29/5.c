#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int input[1000];
    for(int i = 0; i < n; i++){
        scanf("%d", &input[i]);
    }

    for (int i = 0; i < n; i++){
        int temp = 0;
        while (input[i] > 0){
            if (input[i] % 2 ==0){
                input[i] /= 2;
            } else {
                input[i] -= 1;
                temp++;
            }
        }
        printf("%d\n", temp);
    }

}