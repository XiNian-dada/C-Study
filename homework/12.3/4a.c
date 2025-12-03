#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
int main(){
    char str[1001];
    fgets(str,1001,stdin);
    char buffer[1001];
    int i = 0;
    int index = 0;
    while(str[index] != '\0' && str[index] != '\n'){
        if(isalpha(str[index])){
            buffer[i++] = str[index];
        }else{
            for(int j = i-1; j >= 0;j--){
                putchar(buffer[j]);
            }
            putchar(str[index]);
            i=0;
        }
        index++;

    }
    for(int j = i-1; j >= 0; putchar(buffer[j]),j--);
}
