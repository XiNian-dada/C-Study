#include <stdio.h>
int main() { 
    int num;
    scanf("%d", &num);
    int list[num];
    int max = 1, current = 1;
    
    for (int i = 0; i < num; i++) {
        scanf("%d", &list[i]);
    }
    
    for (int i = 0; i < num - 1; i++) {
        if (list[i] + 1 == list[i + 1]) {
            current++;
            if (current > max) {
                max = current;
            }
        } else {
            current = 1;
        }
    }
    
    printf("%d", max);
    return 0;
}