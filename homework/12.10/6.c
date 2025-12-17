#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int main(){
    char str[1001];
    char replace[11];
    memset(replace, '\0', sizeof(replace));
    memset(str, '\0', sizeof(str));
    scanf("%[^\n]",str);
    scanf("%s", replace);
    while(strstr(str,replace) != NULL){
        int start_pos = strstr(str,replace) - str;
        int end_pos = start_pos + strlen(replace);
        for(int i = start_pos; i < end_pos; i++){
            str[i] = '*';
        }
    }
    int is_all_star = 1;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != '*'){
            is_all_star = 0;
            break;
        }
    }
    if(is_all_star){
        printf("null\n");
    }else{
        for(int i = 0; i < strlen(str); i++){
            if(str[i] != '*'){
                printf("%c", str[i]);
            }
        }
    }

}

