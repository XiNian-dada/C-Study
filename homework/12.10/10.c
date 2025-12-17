#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(){
    char s[101];
    memset(s,'\0',sizeof(s));
    fgets(s,101,stdin);
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
        len--;
    } else {
        len = strlen(s);
    }
    int is_in_parentheses = 0;
    int is_in_hash = 0;
    int start_pos[101];
    memset (start_pos,-1,sizeof(start_pos));
    for (int i = 0; i < strlen(s); i++) {
        if(s[i] == '('){
            is_in_parentheses = 1;
        }else if(s[i] == ')'){
            is_in_parentheses = 0;
        }else if(s[i] == '#' && s[i+1] == '#' && i + 1 < strlen(s)){
            if(is_in_parentheses == 0){
                if(is_in_hash == 1) is_in_hash = 0;
                else is_in_hash = 1;
                start_pos[i] = 1;
                start_pos[i+1] = 1;
                i++;
                continue;
            } 
            
        }
        if(is_in_hash == 1){
            start_pos[i] = 1;
        }
    }

    if (is_in_hash == 1) { 
        int index = strlen(s) - 1;
        while (index >= 0 && start_pos[index] == 1) { 
             start_pos[index] = 0;
             index--;
        }
    }
    /*if(start_pos[strlen(s)-1] == 1){
        if(s[strlen(s)-1] != '#'){
            int index = strlen(s)-1;
            while (start_pos[index] != -1){
                start_pos[index] = -1;
                index--;
            }
        }
    }*/
    int is_all_1  = 1;
    for(int i = 0; i < strlen(s)-1; i++){
        if(start_pos[i] != 1){
            is_all_1 = 0;
            break;
        }
    }
    if(is_all_1 == 1){
        printf("NULL\n");
        return 0;
    }
    for(int i = 0; i < strlen(s); i++){
        if(start_pos[i] != 1){
            printf("%c",s[i]);
        }
    }
}