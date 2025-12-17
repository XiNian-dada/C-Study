#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int main(){
    int k;
    char s[101],temp[101];
    memset(temp,'\0',sizeof(temp));
    memset(s,'\0',sizeof(s));
    scanf("%d %s",&k,s);
    int index = 0;
    char* token = strtok(s,"-");
    while(token != NULL){
        for(int i = 0; i < strlen(token); i++){
            temp[index++] = toupper(token[i]);
        }
        token = strtok(NULL,"-");
    }
    int count = 0;
    for(int i = 0; i < index; i++){
        if((index-i) / k >=1){
            printf("%c",temp[i]);
            count++;
            
        }else{
            printf("%c",temp[i]);
            count++;
        }
        if(count % k == 0 && i != index-1) printf("-");
        count %= k;

    }
    if(count == 0){
        return 0;
    }
    for(int i = 0; i < k-count; i++){
        printf("=");
    }

}

