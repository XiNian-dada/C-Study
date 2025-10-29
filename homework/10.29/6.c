#include <stdio.h>
int main() {
    int input;
    int pos[100000];
    int i = 0;
    int sum = 0;
    scanf ("%d", &input);
    if (input == 0) {
        printf("0");
        return 0;
    }
    input = (input > 0)? (input) : (-input);
    while (input != 0){
        
        pos[i] = input % 10;
        input /= 10;
        i++;
    }
    for (int j = 0; j <i; j++){
        sum += pos[j];
    }
    printf("%d", sum);
}