#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
void judge_ipv4(char* origin_ip,int len){ 
    if(origin_ip[len-1] == '\n') origin_ip[len-1] = '\0';
    int dot_num = 0;
    for(int i = 0; i < strlen(origin_ip); i++){
        if(!isdigit(origin_ip[i]) && origin_ip[i] != '.' && origin_ip[i] != '\n' && origin_ip[i] != '\0'){
            printf("NO\n");
            return;
        }
        if(origin_ip[i] == '.')dot_num++;
    }
    if(dot_num != 3){
        printf("NO\n");
        return;
    }
    char* token = strtok(origin_ip, ".");
    while(token != NULL){
        if(atoi(token) < 0 || atoi(token) > 255 || strlen(token)>3 || strlen(token) == 0) {
            printf("NO\n");
            return;
        }
        token = strtok(NULL, ".");
    }
    printf("YES\n");
}
int main(){
    char input[100][31];
    int line = 0;
    while(1){
        fgets(input[line], 31, stdin);
        if (strstr(input[line], "End of file") != NULL) {
            break;  
        }
        line++;
    }
    for(int i = 0; i < line; i++){
        if(strlen(input[i]) > 19 || strlen(input[i])<=7){
            printf("NO\n");
        }else{
            judge_ipv4(input[i],strlen(input[i]));
        }
    }
}