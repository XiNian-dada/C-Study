#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(){
    char s[101];
    memset(s, '\0', 101);
    scanf("%s", s);
    int a_num = 0;
    int successive_l_num = 0;
    char late[3] = {'L','L','L'};
    for(int i = 0; i < strlen(s); i++){
        if(s[i] == 'A'){
            a_num++;
        }
    }
    if(a_num >=2 || strstr(s, "LLL")!=NULL){
        printf("0\n");
    }else{
        printf("1\n");
    }
}

