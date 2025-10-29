#include <stdio.h>

int main(){
    char c[10000];
    int i = 0;
    
    char ch;
    while ((ch = getchar()) != '\n' && i < 9999) {
        c[i] = ch;
        i++;
    }
    i--; 
    int j = 0;
    int temp = 0;
    while (j <= i) {

        if (c[j] == 'a' || c[j] == 'e' || c[j] == 'i' ||
            c[j] == 'o' || c[j] == 'u'){
                printf("%c-",c[j]);
                temp++;
        }
        if (c[j] == 'A' || c[j] == 'E' || c[j] == 'I' ||
            c[j] == 'O' || c[j] == 'U'){
                printf("%c-",c[j]+32);
                temp++;
            }

        j++;
        
        
    }
    printf("%d",temp);
    return 0;
}