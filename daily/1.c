#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int main(){
    char str[10];
    fgets(str,10,stdin);
    int len = strlen(str);
    if(str[len-1] == '\n') len--; 
    int list[10];
    for(int i = len-1;i>=0;i--){
        list[i] = str[i]-'0';
    }
    int flag = 0;
    int sum = 0;
    for(int i = 0;i<len;i++){
        if(flag == 0){
            sum += list[i];
            flag = 1;
        }else if(flag == 1){
            sum -= list[i];
            flag = 0;
        }
    }
    printf("%d\n",sum);
}