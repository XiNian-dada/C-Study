#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int main(){
    char s[1000];
    memset(s, '\0', sizeof(s));
    scanf("%s", s);
    int count = 0;
    int r_num = 0;
    int l_num = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] == 'L'){
            l_num++;
        }else if(s[i] == 'R'){
            r_num++;
        }
        if(l_num == r_num){
            count++;
            l_num = 0;
            r_num = 0;
        }
    }
    printf("%d\n", count);
}

