#include <stdio.h>
#include <ctype.h>
int main(){
    int ch;
    int first_word = 1;
    int space_needed = 0;

    while((ch = getchar()) != EOF){
        if(isspace(ch) && first_word){
            continue;
        }
        if(isalpha(ch)){
            putchar(ch);
            first_word = 0;
            space_needed = 1;
        }else if (ispunct(ch)){
            putchar(ch);
            space_needed = 1;
        }
        if (isspace(ch) && space_needed){
            putchar(' ');
            space_needed = 0;
        } 
    }
    return 0;

}