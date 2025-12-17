#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int times(char *num,char c){
    int count = 0;
    for(int i = 0; i < strlen(num); i++){
        if(num[i] == c){
            count++;
        }
    }
    return count;
}

int main(){
    char num[100],replace[100];
    memset(num,'\0',sizeof(num));
    memset(replace,'\0',sizeof(replace));
    scanf("%s %s",num,&replace);
    char d = replace[0]; 
    if(strstr(num,replace) == NULL){
        printf("%s\n",num); 
        return 0;
    }

    int time = times(num,d);
    int last_d_index = -1; 
    if(time == 1){
        for(int i = 0; i < strlen(num); i++){
            if(num[i] != d){
                printf("%c",num[i]);
            }
        }
        printf("\n");
        return 0;
    }
    
    int f = 0;
    for(int i = 0; i < strlen(num); i++){ 
        if(num[i] == d){
            last_d_index = i; 
            if(i < strlen(num) - 1 && num[i+1] > d){ 
                num[i] = 'N';
                f = 1;
                break;
            }
        }
    }

    if(f == 0){
        if(last_d_index != -1){
             num[last_d_index] = 'N'; 
        }
    }

    for(int i = 0; i < strlen(num) ; i++){
        if(num[i] != 'N'){
            printf("%c",num[i]);
        }
    }
    printf("\n");
    
    return 0;
}